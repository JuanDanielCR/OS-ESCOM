#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[]){
	int status = 0;
	int nivel = 0;
	
	for(int i=0; i<2;i++){
		pid_t pid = fork();
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
				printf("Izquierdo pid: %d  nivel: %d hijo de: %d \n", getpid(), nivel,getppid());
			}else{ //hijo der, pues i = 1
				nivel++;
				printf("Derecho pid: %d nivel: %d hijo de: %d \n", getpid(), nivel,getppid());
			}
			break;
			//los hijos ya no siguen el for(), solo el padre
		}else{
		//error
			printf("%s\n", "Error");
			exit(1);
		}
	}
	return 0;
}

