#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 5
void *PrintHello(void *threadId){
	long tid= (long)threadId;
	printf("Im a: #%ld thread\n",tid);
	pthread_exit(NULL);
}
int main(int argc, char const *argv[]){
	pthread_t threads[5]; 
	int createStatus;

	for (int i = 0; i < NUM_THREADS; ++i){
		printf("Creando a: %d\n", i);
		threads[i] = i;
		pthread_create(&threads[i],NULL,PrintHello, (void*)i);
		if(createStatus == 0){
			printf("%s\n", "----");
		}	
	}
	return 0;
}
/*
	Otra forma:
	main(){
		...
		pthread_create(&threads[i],NULL,PrintHello, (void*)&threads[i]);
		...
	}

	void *PrintHello(void *threadId){
		long *tid = (long*)threadId;
		printf("Im a: #%ld thread\n",*tid);
		pthread_exit(NULL);
	}
*/