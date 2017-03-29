#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int nivel = 0;
int hijos_izq = 0;
int hijos_der = 0;
int status;

void menu();
void crearHijo(int nivel_actual,int numero_hijos, int pid_padre, int hijos_max);

int main(int argc, char const *argv[]) {
	menu();
	int pid = fork();
	if(pid == 0){
	//hijo izq
		printf("Izq: %d hijos: %d hijo de: %d \n", getpid(),hijos_izq, getppid());
    	crearHijo(1,0,getpid(),hijos_izq);
  	}else if(pid > 0){
  	//padre
  		printf("Soy el padre pid: %d con nivel 0 \n", getpid());
    	int pid2 = fork();
    	while(wait(&status) > 0);

    	if(pid2 == 0){
    	//hijo der
    		printf("Der: %d hijos: %d hijo de: %d\n", getpid(),hijos_der,getppid());
    		crearHijo(1,0,getpid(),hijos_der);
    	}
  	}else if(pid < 0){
    	printf("%s\n", "Error");
  	}
  	//printf("%s\n", "bye");
	return 0;
}

void crearHijo(int nivel_actual, int numero_hijos, int pid_padre, int hijos_max){
	if(nivel_actual == nivel){
		//Salir de un proceso hoja
		exit(0);
		return;
	}else{
		nivel_actual++;
		numero_hijos++;
		int hijo = fork();
		if(hijo == 0){
		//hijo
			printf("Soy el proceso %d hijo de %d con nivel %d \n", getpid(),pid_padre,nivel_actual);
			crearHijo(nivel_actual,0, getpid(),hijos_max);
		}else{
		//padre
			if(numero_hijos>=hijos_max){
				//salir del padre
				exit(0);
				return;
			}else{
				crearHijo((nivel_actual-1),numero_hijos,getpid(),hijos_max);
			}
		}
	}
}

void menu(){
	printf("%s", "Nivel: ");
	scanf("%d", &nivel);
	printf("\n %s","# hijos izq: ");
	scanf("%d", &hijos_izq);
	printf("\n %s","# hijos der: ");
	scanf("%d",&hijos_der);
	return ;
}