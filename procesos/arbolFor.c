#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void crearHijo();
int status = 0;
int nivel = 0;

int main(int argc, char const *argv[]){

	int hijosIzq = 0;
	int hijosDer = 0;
	int nivelActual = 0;

	printf("%s\n", "Nivel: ");
	scanf("%d",&nivel);
	printf("%s\n", "Hijos Izquierdos: ");
	scanf("%d",&hijosIzq);
	printf("%s\n", "Hijos Derechos: ");
	scanf("%d",&hijosDer);

	//aplicar esto recursivamente
	for(int i=0; i<2;i++){
		pid_t pid = fork();
		if(pid > 0){
		//padre -- crea hijos con el for()
			printf("Soy el padre pid: %d con nivel 0 \n", getpid());
			if(i==1){
			//ya puedo hacer el wait pues ha esperado ambos hijos
				while(wait(&status) > 0);
				printf("%s\n", "Mis hijos terminaron");
			}
		}else if(pid == 0){
		//en los hijos veo quien es izq y quien der
			nivelActual++;
			if(i == 0){ //hijo izq, pues i=0
				printf("Izquierdo pid: %d  nivel: %d hijo de: %d \n", getpid(), nivelActual,getppid());
				crearHijos(hijosIzq,1);
			}else{ //hijo der, pues i = 1
				printf("Derecho pid: %d nivel: %d hijo de: %d \n", getpid(), nivelActual,getppid());
				crearHijos(hijosDer,1);
			}
			break;
			//los hijos ya no siguen el for(), solo el padre
		}else{
		//error
			printf("%s\n", "Error");
			exit(1);
		}
	}

	return 0;
}

void crearHijos(int numHijos,int nivelActual){

	for(int i=0; i < numHijos;i++){
		pid_t pid = fork();
		if(pid > 0){
		//padre -- crea hijos con el for()
			if(i==(numHijos-1)){
			//ya puedo hacer el wait esperando a todos los hijos
				while(wait(&status) > 0);
			}
		}else if(pid == 0){
		//hijos -- llaman a la recursion() 
			nivelActual++;
			printf("Pid: %d  nivel: %d hijo de: %d \n", getpid(), nivelActual,getppid());
			//Validamos nivel en los hijos
			if(nivelActual < nivel){		
				crearHijos(numHijos,nivelActual);
			}
			break;
			//los hijos ya no siguen el for(), solo el padre
		}else{
		//error
			printf("%s\n", "Error");
			exit(1);
		}
	}
}