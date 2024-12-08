#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>



int contador_sigint = 0; // Contador para o número de vezes que SIGINT foi recebido

// Manipulador para o sinal SIGINT (Ctrl-C)
void sinalINT (int sinal) {
    contador_sigint++; // Incrementa o contador cada vez que Ctrl-C é pressionado

    if (contador_sigint >= 3) {
        // Pergunta se o usuário realmente deseja sair após 3 vezes Ctrl-C
        char mensagem[] = "\nRealmente deseja sair? [S/N]: ";
        write(1, mensagem, sizeof(mensagem) - 1); // Escreve a pergunta no terminal

        alarm(20); // Define o alarme para 20 segundos

        char resposta;
        read(2, &resposta, 1); // Lê a resposta do usuário
        alarm(0); // Cancela o alarme se o usuário responder a tempo

        if (resposta == 'S' || resposta == 's') {
            char sair[] = "Saindo...\n";
            write(1, sair, sizeof(sair) - 1); // Escreve mensagem de saída
            exit(0); // Encerra o programa
        } else {
            if ( resposta == 'N' || resposta == 'n'){
            char continuar[] = "\nContinuando...\n";
            write(1, continuar, sizeof(continuar) - 1); // Escreve mensagem de continuação
            contador_sigint = 0; // Reseta o contador de SIGINT
            }
        }
    }
}

// Manipulador para o sinal SIGTSTP (Ctrl-Z)
void sinalTSTP(int sinal) {
    // Mostra quantas vezes Ctrl-C foi pressionado até agora
    char buffer[50];
    int len = snprintf(buffer, sizeof(buffer), "\nVocê apertou Ctl-C '%d' vezes\n", contador_sigint);
    write(1, buffer, len); // Escreve a informação no terminal
}

// Manipulador para o sinal SIGALRM (disparado quando o usuário demora para responder)
void sinalLRM(int sinal) {
    char mensagem[] = "\nDemorou muito para responder. Saindo...\n";
    write(1, mensagem, sizeof(mensagem) - 1); // Escreve mensagem de tempo esgotado
    exit(0); // Força a saída do programa
}

int main() {
    // Define os manipuladores de sinal
    signal(SIGINT, sinalINT); // Manipula Ctrl-C (SIGINT)
    signal(SIGTSTP, sinalTSTP); // Manipula Ctrl-Z (SIGTSTP)
    signal(SIGALRM, sinalLRM); // Manipula o alarme (SIGALRM)

    // Loop principal do programa, espera por sinais
    while (1) {
        pause(); // Aguarda um sinal para ser tratado
    }

    return 0;
}
