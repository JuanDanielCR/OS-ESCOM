#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/stat.h>
#include <fcntl.h>
#define FIFO_NAME "american_maid"

int main(int argc, char const *argv[])
{
	for(int i=0; i<2;i++){
		pid_t pid = fork();
		if(pid == 0){
		//padre
			char s[300];
		    int num, fd;

		    mknod(FIFO_NAME, S_IFIFO | 0666, 0);

		    printf("waiting for readers...\n");
		    fd = open(FIFO_NAME, O_WRONLY);
		    printf("got a reader--type some stuff\n");

		    while (gets(s), !feof(stdin)) {
		        if ((num = write(fd, &i, sizeof(i))) == -1)
		            perror("write");
		        else
		            printf("speak: wrote %d bytes\n", num);
		    }
		}else if(pid > 0){
		//hijos
			char s[300];
		    int num, fd, o;

		    mknod(FIFO_NAME, S_IFIFO | 0666, 0);

		    printf("waiting for writers...\n");
		    fd = open(FIFO_NAME, O_RDONLY);
		    printf("got a writer\n");

		    do {
		        if ((num = read(fd, &o, sizeof(o))) == -1)
		            perror("read");
		        else {
		            s[num] = '\0';
		            printf("tick: read %d bytes: \"%d\"\n", num, o);
		        }
		    } while (num > 0);
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