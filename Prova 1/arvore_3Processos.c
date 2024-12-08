#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main ( ){

    int pidA, pidB, status; 

    pidA = fork(); // cria processo A

    if (pidA < 0){
        printf("Erro na chamada fork\n");
    } else if (pidA == 0 ){
        pidB = fork(); // processo A cria processo B 

        if (pidB <0){

        }else if (pidB == 0 ){
             printf("Eu sou o processo C, PID: %d, filho de B PID: %d\n", getpid(), getppid()); // Processo C
        } else {
            wait(NULL);
            sleep(1);
            // Processo B
            printf("Eu sou o processo B, PID: %d, filho de A, PID: %d\n", getpid(), getppid() );
          }
    } else {
    wait(NULL);
    sleep (1);
    //Processo A 
    printf("Eu sou o processo A, PID: %d\n", getpid());
    } 


}// fim main 

