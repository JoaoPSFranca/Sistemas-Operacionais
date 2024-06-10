#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define MAXLIN 33
#define MAXCOL 30

HANDLE hThread1, hThread2, hThread3;
HANDLE mutex;
DWORD ThreadID1;

int  pontos = 0;

int pacman[2] = {24, 15};

int fantasma[2][2] = {
    {12, 13},
    {12, 16}
};

int 
    velo = 50, 
    veloFant = 150,
    gameover = 0;

int mapa[MAXLIN][MAXCOL] = {
    {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
    {9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9},
    {9, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9},
    {9, 2, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 4, 4, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 2, 9},
    {9, 2, 0, 4, 9, 9, 4, 0, 4, 9, 9, 9, 4, 0, 4, 4, 0, 4, 9, 9, 9, 4, 0, 4, 9, 9, 4, 0, 2, 9},
    {9, 2, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 2, 9},
    {9, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9},
    {9, 2, 0, 3, 3, 3, 3, 0, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3, 3, 3, 3, 0, 2, 9},
    {9, 2, 0, 3, 3, 3, 3, 0, 4, 4, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 4, 4, 0, 3, 3, 3, 3, 0, 2, 9},
    {9, 2, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 2, 9},
    {9, 1, 1, 1, 1, 1, 1, 0, 4, 3, 3, 3, 3, 9, 4, 4, 9, 3, 3, 3, 3, 4, 0, 1, 1, 1, 1, 1, 1, 9},
    {9, 9, 9, 9, 9, 9, 2, 0, 4, 3, 3, 3, 3, 9, 3, 3, 9, 3, 3, 3, 3, 4, 0, 2, 9, 9, 9, 9, 9, 9},
    {9, 9, 9, 9, 9, 9, 2, 0, 4, 4, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4, 4, 0, 2, 9, 9, 9, 9, 9, 9},
    {9, 9, 9, 9, 9, 9, 2, 0, 4, 4, 9, 1, 1, 1, 8, 8, 1, 1, 1, 9, 4, 4, 0, 2, 9, 9, 9, 9, 9, 9},
    {9, 1, 1, 1, 1, 1, 1, 0, 3, 3, 9, 2, 9, 9, 9, 9, 9, 9, 2, 9, 3, 3, 0, 1, 1, 1, 1, 1, 1, 9},
    {9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 2, 9, 9, 9, 9, 9, 9, 2, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9},
    {9, 1, 1, 1, 1, 1, 1, 0, 3, 3, 9, 2, 9, 9, 9, 9, 9, 9, 2, 9, 3, 3, 0, 1, 1, 1, 1, 1, 1, 9},
    {9, 9, 9, 9, 9, 9, 2, 0, 4, 4, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 4, 4, 0, 2, 9, 9, 9, 9, 9, 9},
    {9, 9, 9, 9, 9, 9, 2, 0, 4, 4, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4, 4, 0, 2, 9, 9, 9, 9, 9, 9},
    {9, 9, 9, 9, 9, 9, 2, 0, 4, 4, 9, 3, 3, 3, 3, 3, 3, 3, 3, 9, 4, 4, 0, 2, 9, 9, 9, 9, 9, 9},
    {9, 1, 1, 1, 1, 1, 1, 0, 3, 3, 9, 3, 3, 3, 4, 4, 3, 3, 3, 9, 3, 3, 0, 1, 1, 1, 1, 1, 1, 9},
    {9, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9},
    {9, 2, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 4, 4, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 2, 9},
    {9, 2, 0, 3, 3, 4, 4, 0, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3, 3, 3, 3, 3, 0, 4, 4, 3, 3, 0, 2, 9},
    {9, 2, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 2, 9},
    {9, 1, 1, 1, 0, 4, 4, 0, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 0, 4, 4, 0, 1, 1, 1, 9},
    {9, 1, 1, 1, 0, 3, 3, 0, 4, 4, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 4, 4, 0, 3, 3, 0, 1, 1, 1, 9},
    {9, 2, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 2, 9},
    {9, 2, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 4, 4, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 2, 9},
    {9, 2, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 2, 9},
    {9, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9},
    {9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9},
    {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}
};

void printMap() {
    system("cls");
    
    int i, j;
    for(i=0;i<MAXLIN;i++) {
        for(j=0;j<MAXCOL;j++) {
            switch(mapa[i][j]) {
                case 0: printf(" %c ", 250); break;                 // quadradinho do ponto
                case 1: printf("%c%c%c", 205, 205, 205); break;     // barra dupla deitada
                case 2: printf(" %c ", 186); break;                 // barra dupla em pé
                case 3: printf("%c%c%c", 196, 196, 196); break;     // barra simples deitada
                case 4: printf(" %c ", 179); break;                 // barra simples em pé
                case 8: printf("%c%c%c", 176, 176, 176); break;     // light shade
                case 9: printf("   "); break;                       // espaço
            }
        }
        printf("\n");
    }
}

void gotoxy(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

void desenharPacman(){
    gotoxy(pacman[1] * 3, pacman[0]);
    printf(" %c ", 64);
}

void apagaPacman(){
    gotoxy(pacman[1] * 3, pacman[0]);
    printf("   ");
}

void andarPacman(int direcao){
    WaitForSingleObject(mutex,INFINITE);
    apagaPacman();

    switch (direcao) {
        case 0: pacman[0]--; break;
        case 1: pacman[0]++; break;
        case 2: pacman[1]--; break;
        case 3: pacman[1]++; break;
    }

    desenharPacman();
    Sleep(velo);
    ReleaseMutex(mutex);
}

void apagaFantasma(int fant[2]){
    gotoxy(fant[1] * 3,fant[0]);
    switch(mapa[fant[0]][fant[1]]) {
        case 0: printf(" %c ", 250); break;                 // quadradinho do ponto
        case 8: printf("%c%c%c", 176, 176, 176); break;     // light shade
        case 9: printf("   "); break;                       // espaço
    }
}

void desenharFantasma(int fant[2]){
    gotoxy(fant[1] * 3, fant[0]);
    printf(" %c ", 219);
}

void andarFantasma(int direcao, int i){
    WaitForSingleObject(mutex,INFINITE);
    apagaFantasma(fantasma[i]);

    switch (direcao) {
        case 0: fantasma[i][0]--; break;
        case 1: fantasma[i][0]++; break;
        case 2: fantasma[i][1]--; break;
        case 3: fantasma[i][1]++; break;
    }

    desenharFantasma(fantasma[i]);
    Sleep(veloFant);
    ReleaseMutex(mutex);
}

void configurartela(void) {
    //Define um estrutura que representa o cursor da tela
    CONSOLE_CURSOR_INFO info;

    //Define uma variavel para representar o console
    HANDLE wHnd;
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

    //Define a cor do fundo e da fonte
    system("color 07");

    //Muda o titulo da janela
    SetConsoleTitle("Pacman em C");

    //Define o tamanho da janela
    SMALL_RECT windowSize = {0, 0, (MAXCOL*3)+1, MAXLIN+5};
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

    //Define o tamanho do buffer:
    COORD bufferSize = {(MAXCOL*3)+1, MAXLIN+5};
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    //Apaga o cursor da tela
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(wHnd, &info);

    printMap();
    desenharFantasma(fantasma[0]);
    desenharFantasma(fantasma[1]);
    desenharPacman();
}

int verificarPosicao(int x, int y){
    WaitForSingleObject(mutex,INFINITE);
    int verify = 0;

    switch (mapa[x][y]) {
        case 0: pontos++; mapa[x][y] = 9; verify = 1; break;
        case 9: verify = 1; break;
        default: verify = 0; break;
    }

    if(x == fantasma[0][0] && y == fantasma[0][1])
        { gameover = 1; verify = 1; }
    
    if(x == fantasma[1][0] && y == fantasma[1][1])
        { gameover = 1; verify = 1; }

    ReleaseMutex(mutex);
    return verify;
}

DWORD WINAPI moverPacman(LPVOID lpParam) {
    int tecla = 0;

    while(gameover==0){
        WaitForSingleObject(mutex,INFINITE);
        gotoxy(0, MAXLIN+1);
        printf("Pontos: %d\t",pontos);
        ReleaseMutex(mutex);
        
        if(kbhit())
            tecla=getch();

        // pra cima
        if(tecla=='w' || tecla=='W' || tecla==72){
            if(verificarPosicao(pacman[0] - 1, pacman[1])){
                andarPacman(0);
            }
        }

        // pra baixo                  
        if(tecla=='s' || tecla=='S' || tecla==80){
            if(verificarPosicao(pacman[0] + 1, pacman[1])){
                andarPacman(1);
            }
        }

        // pra esquerda
        if(tecla=='a' || tecla=='A' || tecla==75){
            if(verificarPosicao(pacman[0], pacman[1] - 1)){
                andarPacman(2);
            }
        }

        // pra direita         
        if(tecla=='d' || tecla=='D' || tecla==77){
            if(verificarPosicao(pacman[0], pacman[1] + 1)){
                andarPacman(3);
            }
        }
    }
        
    return 0;
}


int verificarPosicaoFantasma(int x, int y, int i){
    WaitForSingleObject(mutex,INFINITE);

    int verify = 0;

    switch (mapa[x][y]) {
        case 0: verify = 1; break;
        case 8: verify = 1; break;
        case 9: verify = 1; break;
        default: verify = 0; break;
    }

    if(x == pacman[0] && y == pacman[1])
        { gameover = 1; verify = 1; }
    
    if (i == 0){
        if(x == fantasma[1][0] && y == fantasma[1][1]){
            verify = 0;
        }
    } else {
        if(x == fantasma[0][0] && y == fantasma[0][1]){
            verify = 0;
        }
    }

    ReleaseMutex(mutex);
    
    return verify;
}

DWORD WINAPI moverFantasma(LPVOID lpParam) {
    int i = *((int*)lpParam);

    while(gameover==0){
        int numero = rand() % 4;

        switch (numero) {
            case 0: // pra cima
                if(verificarPosicaoFantasma(fantasma[i][0] - 1, fantasma[i][1], i))
                    andarFantasma(0, i);
                break;
            case 1: // pra baixo
                if(verificarPosicaoFantasma(fantasma[i][0] + 1, fantasma[i][1], i))
                    andarFantasma(1, i);
                break;
            case 2: // pra esquerda
                if(verificarPosicaoFantasma(fantasma[i][0], fantasma[i][1] - 1, i))
                    andarFantasma(2, i);
                break;
            case 3: // pra direita
                if(verificarPosicaoFantasma(fantasma[i][0], fantasma[i][1] + 1, i))
                    andarFantasma(3, i);
                break;
        }
    }

    return 0;
}


int main() {
    mutex = CreateMutex(NULL, FALSE, NULL);
    
    if (mutex == NULL) {
        printf("Erro ao criar o mutex!!");
        return 1;
    }
    
    srand(time(NULL));

    configurartela();

    // pacman
    hThread1 = CreateThread(NULL, 0, moverPacman, NULL, 0, &ThreadID1);

    int a = 0;
    // fantasma 1
    hThread2 = CreateThread(NULL, 0, moverFantasma, &a, 0, NULL);

    int b = 1;
    // fantasma 2
    hThread3 = CreateThread(NULL, 0, moverFantasma, &b, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    WaitForSingleObject(hThread3, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);
    CloseHandle(hThread3);

    system("cls");
    printf("Voce perdeu! Fez %d pontos.\n",pontos);
    system("pause");
    return 0;
}
