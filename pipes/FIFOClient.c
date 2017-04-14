#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/stat.h>

int main(int argc, char const *argv[])
{
	FILE *fp;
	char readBuffer[80];

	/*Create FIFO*/
	mknod("myfifo",S_IFIFO|0666,0);

	/*Open FIFO and write to it*/
	while(1){
		fp = fopen("myfifo","r");
		fgets(readBuffer, 80, fp);
		printf("GET: %s\n", readBuffer);
		fclose(fp);
	}
	return 0;
}