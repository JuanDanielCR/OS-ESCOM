#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/stat.h>


int main(int argc, char const *argv[])
{
	int fd[2]; 
	char string[] = "Hello father from pipe \n";
	int readbuffer,n;

	//Creación del pipeline, antes del fork(), para que el hijo herede el pipe del padre
	

	for(int i=0; i<5;i++){
		pipe(fd);
		pid_t pid = fork();
		if(pid == 0){
		//padre
			close(fd[1]);
			while ((n = read(fd[0], &readbuffer, sizeof(readbuffer))> 0)) { // Read until it returns 0 (EOF) or -1 (error)
			    printf("Soy el padre, recibí: %d\n", readbuffer);
			}
			//read(file_descriptor, var to save data_readed, size)
		}else if(pid > 0){
		//hijos
			close(fd[0]);
			//write(file_descriptor, data_to_send, size)
			int aux = i;
			printf("hijo: %d\n", aux);
			for(int i = 5; i < 20; i++){
				write(fd[1],&i, sizeof(aux));
			}
			close(fd[1]);
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