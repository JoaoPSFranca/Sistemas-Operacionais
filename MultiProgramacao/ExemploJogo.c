#include <stdio.h>
#include <windows.h>

#define MAXLIN 24
#define MAXCOL 79
#define MAXTIRO 100

typedef struct tipotiro {
  HANDLE thread;
  int lin, col;
  char status;
} tiro;

HANDLE mutex;
tiro tiros[MAXTIRO];
int i_tiros = 0;

void configurartela(void) {
  //Define um estrutura que representa o cursor da tela
  CONSOLE_CURSOR_INFO info;

  //Define uma variavel para representar o console
  HANDLE wHnd;
  wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

   //Define a cor do fundo e da fonte
  system("color 0E");

  //Muda o titulo da janela
  SetConsoleTitle("*** J O G O   D O   J O T A P E ***");

  //Define o tamanho da janela
  SMALL_RECT windowSize = {0, 0, MAXCOL+1, MAXLIN+1};
  SetConsoleWindowInfo(wHnd, 1, &windowSize);

  //Define o tamanho do buffer:
  COORD bufferSize = {MAXCOL+1, MAXLIN+1};
  SetConsoleScreenBufferSize(wHnd, bufferSize);

  //Apaga o cursor da tela
  info.dwSize = 100;
  info.bVisible = FALSE;
  SetConsoleCursorInfo(wHnd, &info);
}

void gotoxy(int x, int y) {
  COORD coord;
  coord.X=(short)x;
  coord.Y=(short)y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void imprimirnave(void) {
  printf("%c",195);
}

void apagarnave(void) {
  printf(" ");
}

void imprimirtiro(void) {
  printf("-");
}

void apagartiro(void) {
  printf(" ");
}

void movertiro(int pos) {
  while(tiros[pos].col<MAXCOL) {
    WaitForSingleObject(mutex,INFINITE);
    gotoxy(tiros[pos].col,tiros[pos].lin);
    imprimirtiro();
    ReleaseMutex(mutex);
    _sleep(30);
    WaitForSingleObject(mutex,INFINITE);
    gotoxy(tiros[pos].col,tiros[pos].lin);
    apagartiro();
    tiros[pos].col++;
    ReleaseMutex(mutex);
  }
  WaitForSingleObject(mutex,INFINITE);
  tiros[pos].status=0; //morto
  ReleaseMutex(mutex);
  _endthread();
}

int main() {
  int linNave=12,colNave=0;
  char tecla;
  mutex = CreateMutex(NULL,FALSE,NULL);
  configurartela();
  gotoxy(colNave,linNave);
  imprimirnave();
  while(1) {
    tecla=getch();
    switch(tecla) {
      case 32: ///Barra de espaco
        WaitForSingleObject(mutex,INFINITE);
        tiros[i_tiros].lin = linNave;
        tiros[i_tiros].col = colNave+1;
        tiros[i_tiros].status = 1; //vivo
        tiros[i_tiros].thread = _beginthread(movertiro,0,i_tiros);
        
        //Adiciona tiros no vetor de tiros
        do {
          if (i_tiros < MAXTIRO-1)
            i_tiros++;
          else
            i_tiros=0;
        } while(tiros[i_tiros].status!=0);
        ReleaseMutex(mutex);
        break;
      case -32: ///Tecla especial
        tecla=getch();
        //printf("%d",tecla);
        switch(tecla) {
          case 72: ///Tecla para cima
            if (linNave>0) {
              WaitForSingleObject(mutex,INFINITE);
              gotoxy(colNave,linNave);
              apagarnave();
              ReleaseMutex(mutex); 
              linNave--;
              WaitForSingleObject(mutex,INFINITE);
              gotoxy(colNave,linNave);
              imprimirnave();
               ReleaseMutex(mutex);
            }
            break;
          case 80: ///Tecla para baixo
            if (linNave<MAXLIN) {
              WaitForSingleObject(mutex,INFINITE);
              gotoxy(colNave,linNave);
              apagarnave();
              ReleaseMutex(mutex);
              linNave++;
              WaitForSingleObject(mutex,INFINITE);
              gotoxy(colNave,linNave);
              imprimirnave();
              ReleaseMutex(mutex);
            }
            break;
        }
    }
  }

  return 0;
}