#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
//estructura a guardar
	struct Llamada{
		char[50] nombre;
		char[10] telefono;
		char[20] proveedor;

	};

int main(int argc, char const *argv[]){
	int idSegmento;
//Generación de la llave
	key_t key = ftok("/bin/ls","J");
//Creacion de un segmento de memoria
	idSegmento = shmget(key,sizeof(struct Llamada),IPC_CREAT);
//IPC_EXCL devuelve un fallo si es ue ya existe la memoria, para que solo me linkee a ella
	return 0;
}