#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/stat.h>

int main(int argc, char const *argv[])
{
	FILE *fp;
	char readBuffer[80];
	int stop = 0;
	/*Create FIFO*/
	mknod("myfifo",S_IFIFO|0666,0);

	/*Open FIFO and read to it*/
	while(1){
		fp = fopen("myfifo","r");
		fgets(readBuffer, 80, fp);
		printf("GET: %s\n", readBuffer);
		fclose(fp);
		stop++;
		if(stop == 2){ //receive 2 messages
			break;
		}
	}
	printf("%s\n", "Sali");
	return 0;
}