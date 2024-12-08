#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int valor = 10;  // Variável compartilhada entre o processo pai e o processo filho

    pid_t pid = fork();

    if (pid == -1) {
        // Caso ocorra um erro no fork
        perror("Erro ao criar o processo filho");
        exit(1);
    } else if (pid == 0) {
        // Processo filho
        printf("Processo filho: valor = %d\n", valor);
        valor = 20;  // Modifica o valor apenas no processo filho
        printf("Processo filho (após modificação): valor = %d\n", valor);
        exit(0);
    } else {
        // Processo pai
        wait(NULL);  // Aguarda o processo filho terminar
        printf("Processo pai: valor = %d\n", valor);  // O valor permanece inalterado no processo pai
    }

    return 0;
}

