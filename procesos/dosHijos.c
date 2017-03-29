#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
	int status = 0;
	int nivel = 0;
	for(int i=0; i<2;i++){
		int pid = fork();
		if(pid > 0){
		//padre
			printf("Soy el padre pid: %d con nivel 0 \n", getpid());
			if(i==1){
			//ya puedo hacer el wait pues ha esperado ambos hijos
				while(wait(&status) > 0);
			}
		}else if(pid == 0){
		//en los hijos veo quien es izq y quien der
			if(i == 0){ //hijo izq, pues i=0
				nivel++;
				printf("Soy el izquierdo pid: %d con nivel: %d hijo de:\n", getpid(), nivel,getppid());
			}else{ //hijo der, pues i = 1
				nivel++;
				printf("Soy el derechi pid: %d con nivel: %d hijo de: \n", getpid(), nivel,getppid());
			}
		}else{
		//error
			printf("%s\n", "Error");
			exit(1);
		}
	}
	return 0;
}