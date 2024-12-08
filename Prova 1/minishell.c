#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void lista_arquivos() {
    execl("/bin/ls", "ls", "-l", NULL); // executa o comando ls-l para listar os arq do diretorio atual 
}

void lista_processos() {
    execl("/bin/ps", "ps", "aux", NULL); // executa o coamndo ps aux para mostrar os processos em execução 
}

void info_rede() {
    execl("/sbin/ifconfig", "ifconfig", NULL); // executa o comando ifconfig para exibir informações de rede 
}

void menu() {
    printf("\n\nComandos disponíveis:\n");
    printf(" - listar: Lista todos os arquivos do diretório atual\n");
    printf(" - processos: Mostra informações sobre os processos em execução\n");
    printf(" - rede: Mostra informações da rede e IP\n");
    printf(" - socorro: Exibe esta lista de comandos\n");
}

int main() {
    char comando[100];
    char argumento[100];

    while (1) {
        menu();
        printf("Digite a opção desejada do Mini Shell> ");
        fgets(comando, sizeof(comando), stdin);
        comando[strcspn(comando, "\n")] = 0;  // Remove newline

        // Separar comando e argumento
        char *token = strtok(comando, " ");
        if (token == NULL) continue;
        strcpy(comando, token);
        token = strtok(NULL, " ");
        if (token != NULL) strcpy(argumento, token);

        pid_t pid = fork(); // cria um processo filho 

        if (pid == 0) {  // Processo filho
            if (strcmp(comando, "listar") == 0) {
                lista_arquivos();
            } else if (strcmp(comando, "processos") == 0) {
                lista_processos();
            } else if (strcmp(comando, "rede") == 0) {
                info_rede();
            } else if (strcmp(comando, "socorro") == 0) {
                menu();
            } else {
                printf("Comando desconhecido. Digite 'socorro' para ajuda.\n");
            }
            exit(0);
        } else {  // Processo pai
            wait(NULL);  // Espera o processo filho
        }
    }

    return 0;
}
