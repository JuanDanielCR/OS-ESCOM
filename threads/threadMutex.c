#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_HILOS 2
/*
	Instrucciones de Preprocesador
*/
int zonaCritica[10];

void *consumidor(void *args){
	//Entra al arreglo 5 veces
	int aux = 0;
	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < 10; ++j){
			zonaCritica[j] = aux;
			aux++;
		}
	}
}
void *productor(void *args){
	int aux = 0;
	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < 10; ++j){
			printf("%d \t",zonaCritica[j]);
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[]){
	
	pthread_t idConsumidor;
	pthread_t idProductor;

	int i;
	for (i = 0; i < NUM_HILOS; ++i){
		if(i == 0){ 
		//Productor
			pthread_create(&(idProductor),NULL,productor,NULL);
		}else{
		//Consumidor
			pthread_create(&(idConsumidor),NULL,consumidor,NULL);
		}	
	}
	for(i = 0; i < NUM_HILOS; i++){
		if(i == 0){ 
		//Productor
			pthread_join(idConsumidor, NULL);
		}else{
		//Consumidor
			pthread_join(idProductor, NULL);

		}	
	}
	
	
	return 0;
}