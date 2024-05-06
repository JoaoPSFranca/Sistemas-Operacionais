#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main(void) {
    int qtd_processos, i, pid, cont, verify;

    printf("Digite a quantidade de processos filho a serem criados: ");
    scanf("%d", &qtd_processos);

    int filhos[qtd_processos];

    for (i = 0; i < qtd_processos; i++) {
        pid = fork();

        if (pid == 0)
            while(1);
        else
            filhos[i] = pid;
    }

    do {
        cont = 0;
        for (i = 0; i < qtd_processos; i++){
            if(filhos[i] != -2){
                printf("Pai - O processo %d esta rodando...\n", filhos[i]);
                cont++;
            }
        }

        if(cont != 0){
            printf("Digite o PID do processo a ser finalizado: ");
            scanf("%d", &pid);

            verify = 0;
            for (i = 0; i < qtd_processos; i++) {
                if (filhos[i] == pid) {
                    verify = 1;
                    kill(pid, 9);
                    filhos[i] = -2;
                }
            }

            if (verify == 0)
                printf("PID invalido. \n");
            else
                printf("O processo filho %d acabou de falecer...\n",pid);
        } 
    } while (cont != 0);

    printf("Todos os processos filhos foram finalizados. Encerrando o processo pai.\n");
    return 0;
}