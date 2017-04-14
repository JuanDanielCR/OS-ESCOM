#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

//implementing $ ls | wc -l
int main(int argc, char const *argv[])
{
	printf("%s \n","Execute ls | wc -l and see the magic" );
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if(pid > 0){
	//padre
		close(1); //close stdout
		dup(fd[1]); //make default stdout = fd[1], the output of the pipe is now the new defult
		close(fd[0]);
		execlp("ls","ls",NULL); //The ls program now uses the pipe and makes a call to write() internally
	}else if(pid == 0){
	//hijo
		close(0);
		dup(fd[0]);
		close(fd[1]);
		execlp("wc","wc","-l",NULL);
	}else{
		printf("%s\n", "Error");
		return 1;
	}
	//This will not apper in cmd, now it will be send through the pipe, 'cause stdout now is fd[1]
	printf("%s\n","Execute ls | wc -l and see the magic" );
	return 0;
}