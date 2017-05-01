#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 5
struct thread_data{
	int thread_id;
	int sum;
};

//my array of structures
struct thread_data array_of_threads[NUM_THREADS];

void *PrintHello(void *args){
	struct thread_data *mydata = (struct thread_data*) args;
	int id = mydata->thread_id;
	int sum  = mydata->sum;
	printf("Id: %d | sum: %d\n", id,sum);
	/*
		No retornar variable locales de cada thread
	*/
	pthread_exit((void *)args); 
	/*
		Also:
		struct thread_data mydata = *(struct thread_data*) args;
		int id = mydata.thread_id;
		int sum  = mydata.sum;
	*/
}

int main(int argc, char const *argv[]){
	pthread_t threads[5]; 
	int createStatus;
	int sum = 0;
	void *devuelto;
	for (int i = 0; i < NUM_THREADS; ++i){
		threads[i] = i;
		sum = sum +i;
		printf("Creando a: %d\n", i);
	//fill the structure
		array_of_threads[i].thread_id = i;
		array_of_threads[i].sum = sum;

		pthread_create(&(threads[i]),NULL,PrintHello, (void*)&array_of_threads[i]);
		
		if(createStatus == 0){
			printf("%s\n", "----");
		}	
	}
	//REcuperación de valores con join
	for(int j = 0; j < NUM_THREADS; j++){
		pthread_join(threads[j],(void*)&devuelto);
		struct thread_data *esctructuraVuelta = (struct thread_data*) devuelto;
		printf("Devuelta: %d\n",esctructuraVuelta->sum);
	}

	return 0;
}
