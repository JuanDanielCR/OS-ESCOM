#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	//matriz
	int m1 = {{1,2,3,1},{1,2,3,1},{1,2,3,1},{1,2,3,1}};
	int m2 = {{1,2,3,1},{1,2,3,1},{1,2,3,1},{1,2,3,1}};
	int status;
	//creando procesos
	int numProcesos = 2;
	int filas = 4;
	int columnas = 4;
	int tarea = filas/numProcesos;
	pid_t proceso;
	for(int i = 0; i < numProcesos; i++){
		proceso = fork();
		if(proceso == 0){
		//hijo
			int matriz3[tarea][columnas];
			//interaciones
			for(int j = (tarea*i)-tarea; j < (tarea*i)-1;k++){
				for(int k = 0; k < columnas; k++){
					//pipe(), pero por ahora usamos un tercer for()
					for(int l = 0; l < filas; l++){
						matriz3 [j%tarea][k] += m1[j][k] * m2[l][j];
					}
				}
			}

		}else if(proceso > 0){
		//padre
			if(i == numProcesos-1){
				while(wait(&status)>0)
			}
		}else{
		//error
			printf("%s\n", "Error");
			exit(0);
		}
	}
	return 0;
}