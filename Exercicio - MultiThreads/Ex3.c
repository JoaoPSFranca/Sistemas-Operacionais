/* 3) Desenvolva um programa que crie duas threads no windows. Cada uma delas fará com que um caractere (passado por parâmetro) 
"ande" em uma determinada linha da tela (também passada por parâmetro) até chegar na ultima coluna. 
Assim que chegar na ultima coluna, o caractere deve voltar até a primeira coluna, repetindo o movimento até o usuário 
pressionar CTRL+C. A velocidade de cada thread também deverá ser passada por parâmetro. Utilize uma struct para passar 
mais de um parâmetro para a thread. */

#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <conio.h>
#define N 10

struct param {
    char c;
    int linha;
    int velocidade;
};

void thread(void *p) {
    struct param *p1 = (struct param *) p;

    while (1) {
        for (int i = 0; i < N; i++) {
            printf("%c", p1->c);
            Sleep(p1->velocidade);
        }
        for (int i = 0; i < N; i++) {
            printf("\b");
            Sleep(p1->velocidade);
        }
    }
}

int main() {
    struct param p1 = {'*', 1, 100};
    struct param p2 = {'#', 2, 50};

    _beginthread(thread, 0, &p1);
    _beginthread(thread, 0, &p2);

    while (1) {
        if (kbhit()) {
            getch();
            break;
        }
    }

    return 0;
}