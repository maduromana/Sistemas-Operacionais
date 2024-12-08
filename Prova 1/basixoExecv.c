#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        // Caso ocorra erro no fork
        perror("fork falhou");
        exit(1);
    } else if (pid == 0) {
        // Processo filho
        char *args[] = {"/bin/ls", "-l", NULL};  // Argumentos para o execv
        execv("/bin/ls", args);  // Substitui o filho para executar 'ls -l'
        
        // Se execv falhar, exibe um erro
        perror("execv falhou");
        exit(1);
    } else {
        // Processo pai
        printf("Processo pai aguardando o filho.\n");
        wait(NULL);  // Espera o filho terminar
        printf("Filho terminou.\n");
    }

    return 0;
}

