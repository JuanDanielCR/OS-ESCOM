#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/stat.h>
int status;

int main(int argc, char const *argv[])
{

	FILE *fp;
	int readBuffer;
	int stop = 0;
	mknod("myfifotree",S_IFIFO|0666,0);


	for(int i=0; i<5;i++){
		pid_t pid = fork();
		if(pid > 0){
		//padre
			if(i == 4){
				while(1){
					fp = fopen("myfifotree","r");
					fgets(readBuffer, sizeof(readBuffer), fp);
					printf("GET: %d\n", readBuffer);
					fclose(fp);
					stop++;
					if(stop == 4){ //receive 2 messages
					break;
					}	
				}
			}
			//read(file_descriptor, var to save data_readed, size)
		}else if(pid == 0){
		//hijos
				if((fp=fopen("myfifotree","w"))==NULL){
					printf("%s\n", "Pipe not found");
					exit(1);
				}
				/*Write onto file first passed arg*/
				printf("%d\n",i );
				fputs(i, fp);
			    fclose(fp);
			//los hijos ya no siguen el for(), solo el padre
		}else{
		//error
			printf("%s\n", "Error");
			exit(1);
		}	
	}	
	return 0;
}