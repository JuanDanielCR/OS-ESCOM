#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[]){
	// file descriptors: fd[0] - stdin, fd[1] - stdout
	int fd[2]; 
	char string[] = "Hello father from pipe \n";
	char readbuffer[80];

	//Creación del pipeline, antes del fork(), para que el hijo herede el pipe del padre
	pipe(fd);

	//Creación del hijo
	pid_t child = fork();

	if(child > 0){
	//padre
		//Cerrar la escritura en el padre
		close(fd[1]);
		//read(file_descriptor, var to save data_readed, size)
		read(fd[0], readbuffer, sizeof(readbuffer));
		printf("Soy el padre, recibí: %s\n", readbuffer);
		//read(0, readbuffer, sizeof(readbuffer)); -- lee desde stdin 
	}else if( child == 0){
	//hijo
		//Cerrar la lectura en el hijo, solo dejamos la escritura; fd[0] == &fd[0]
		close(fd[0]);
		//write(file_descriptor, data_to_send, size)
		write(fd[1],string,(strlen(string)+1));
	}else{
		printf("%s\n", "Error");
		exit(1);
	}
	return 0;
}