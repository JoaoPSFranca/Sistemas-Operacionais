#include <stdlib>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "libs/ghost.h"
#include "libs/map.h"
#include "libs/pacman.h"
#include "libs/point.h"

#define MAXLIN 42
#define MAXCOL 40

void configurartela(void) {
    //Define um estrutura que representa o cursor da tela
    CONSOLE_CURSOR_INFO info;

    //Define uma variavel para representar o console
    HANDLE wHnd;
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

    //Define a cor do fundo e da fonte
    system("color 07");

    //Muda o titulo da janela
    SetConsoleTitle("PAC-MAN");

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

int main() {
    configurartela();

    return 0;
}