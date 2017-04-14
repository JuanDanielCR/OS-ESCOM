#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	FILE *fp;
	if ( argc != 2 ) {
        printf("USAGE: fifoclient [string]\n");
        exit(1);
    }
	/*See if FIFO file already exists*/
	if((fp=fopen("myfifo","w"))==NULL){
		printf("%s\n", "Pipe not found");
		exit(1);
	}
	/*Write onto file first passed arg*/
	fputs(argv[1], fp);
    fclose(fp);
	return 0;
}