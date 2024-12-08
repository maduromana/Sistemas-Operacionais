	
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(){
  int status;
  int pid = fork(); 
  if(pid == 0){
      printf("Sou o processo filho e meu pid = %d\n", getpid());
      char c =getchar();
      if(c == 's')
          exit(0);
      else
          while(1);
      
  }else if(pid < 0){
      perror("Erro na criação do processo\n");
  }else{
      printf("Sou o processo pai e meu pid = %d\n", getpid());
      wait(&status);
      if(WIFEXITED(status))
        printf("Processo filho pid %d terminou normalmente\n\n", pid);
      if(WIFSIGNALED(status))  
        printf("Processo filho pid %d terminou forçadamente\n\n", pid);
 }
 
  return 0;

}


