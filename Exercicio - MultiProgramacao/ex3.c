#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main(void) {
    int qtd_processos, i, pid, seg;

    printf("Digite a quantidade de processos filho a serem criados: ");
    scanf("%d", &qtd_processos);

    printf("Digite o tempo que ficarao bloqueados: ");
    scanf("%d", &seg);

    for (i = 0; i < qtd_processos; i++) {
        pid = fork();

        if (pid == 0){
            sleep(seg);
            break;
        }
    }

    if(pid != 0){
        do {
            pid = wait(0);

            if (pid != -1) {
                printf("O processo %d acabou de falecer...\n", pid);
            }
        } while (pid != -1);
    }
    
    printf("Todos os processos filhos foram finalizados. Encerrando o processo pai.\n");
    return 0;
}