/* 2) Faça um programa que crie um número de threads definido pelo usuário. Cada uma 
das threads deve imprimir infinitamente (até o usuário digitar CTRL+C) o número 
de sua criação (ex: a primeira thread criada deverá imprimir o número 1, a 
segunda o número 2 e assim por diante) e um caractere (todas as threads devem 
imprimir o mesmo caractere - variável global) definido pelo usuário. Enquanto as 
threads estiverem imprimindo, assim que o usuário pressionar uma tecla, o 
caractere que está sendo impresso deve ser modificado pelo caractere da tecla 
pressionada. Pode ser necessário utilizar a função kbhit(), que indica se uma 
tecla foi pressionada, e a função getch(), que lê um caractere do teclado sem 
ecoá-lo (não imprime o caractere na tela) e sem a necessidade de pressionar a 
tecla <ENTER>. */

#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <conio.h>
#include <signal.h>

int n_threads;
char caractere;
BOOL running = TRUE;

void thread_func(void *arg) {
    int id = (int) arg;

    while (running) {
        printf("%d %c\n", id, caractere);
        Sleep(1000);

        if (_kbhit()) {
            caractere = _getch();
            printf("Character changed to %c\n", caractere);
        }
    }
}

void signal_handler(int signal) {
    if (signal == SIGINT) {
        running = FALSE;
    }
}

int main() {
    signal(SIGINT, signal_handler);

    printf("Digite o numero de threads: ");
    scanf("%d", &n_threads);

    printf("Digite o caractere: ");

    scanf(" %c", &caractere);

    HANDLE *threads = (HANDLE *) malloc(n_threads * sizeof(HANDLE));

    for (int i = 0; i < n_threads; i++)
        threads[i] = (HANDLE) _beginthread(thread_func, 0, (void *) i);

    WaitForMultipleObjects(n_threads, threads, TRUE, INFINITE);

    for (int i = 0; i < n_threads; i++)
        CloseHandle(threads[i]);

    free(threads);

    return 0;
}