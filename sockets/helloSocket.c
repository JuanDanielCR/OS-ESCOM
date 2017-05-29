#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

struct sockaddr_in servidor, cliente;

//tamaño del buffer a envíar
char buffer[50];

/***SERVIDOR***/
int main(int argc, char const *argv[]){
	int puerto = atoi(argv[1]);
	/*
		Paso 0 creación del socket, parametros de socket:
		Dominios:
			AF_UNIX - local, AF_INET - conexiones remotas
		
		Tipos:
			SOCK_STREAM - TCP
			SOCK_DGRAM  - UDP
		
		Protocolos:
			0 - El protocolo más apropiado
	*/
	int socketId;
	if((socketId = socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("Error construccion del socket");
		exit(1);
	}
	/*
		Paso 1: Publicar el socket como servicio, para que
		los clientes puedan acceder a el.

		Params:
		Id del socket

		Struct: Para asignar la dirección IP y el puerto
		htons: host_to_network_host
		sin_addr es otra struct
		INADDR_ANY macro que obtiene la dir IP por default del dispostivo
	*/
	
	//Llenamos nuestra struct que será el param d bind()
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(puerto);
	servidor.sin_addr.s_addr = INADDR_ANY;

	if(bind(socketId,(struct sockaddr*)&servidor,sizeof(servidor))==-1){
		perror("Error en el bind");
		exit(1);
	}
	/*
		Paso 2: Poner el socket esperando una solicitud (request)
		listen() params:

		Id del socket
		Num de conexiones que puede poner en "queue",
		atiende 1 y pone las otras 3 en cola, pero lo haremos paralelo
	*/
	if(listen(socketId,4)==-1){
		perror("No escucha peticiones");
		exit(1);
	}

	/*
		Paso 3: Aceptar una conexión
		params:
			socketId
			apuntador a struct sock_addr
		Devuelve el id del canal de conexion entre cliente y servidor,
		se necesita entre otras cosas por que es una comuniación orientada
		a conexión y cada paquete tendra un orden para cada conexión diferente
	*/
	int size = sizeof(cliente);
	int canalId;
	if((canalId = accept(socketId,(struct sockaddr*)&cliente, &size))==-1){
		perror("No acepte una conexión");
		exit(1);
	}

	/*
		Paso 4: Zona de comunicación
		send() y recv()

		send() - funcion por default también existe write() pues son vistos como un archivo
		params: idCanal, buffeer a enviar (struct para el proyecto)
		Devuelve el número de caracateres enviados
	*/
	strcpy(buffer,"Hola soy el servidor y te observo");
	if(send(canalId,(void *)buffer, strlen(buffer),0)==-1){
		perror("No se envío mensaje");
		exit(1);
	}
	/*
		Recibir un msj
		Misma firma, pero la diferencia esta en el size.
		En el send pongo exactamente en num de bytes que paso, puede 
		que buffer valga 50 bytes pero solo ocupo 10, así que solo mando 10

		En el receiver si uso un siszeof() por que no se cuanto voy a recibir 
		así que le digo que pueda recibir el máximo
	*/
	unsigned int bytesRecibidos;
	if((bytesRecibidos = recv(canalId,(void *)buffer,sizeof(buffer),0))==-1){
		perror("No se recibio el msj\n");
		exit(1);
	}

	buffer[bytesRecibidos]='\0';
	printf("%s\n", buffer);

	/*Cerrar unicamente el canal*/
	close(canalId);
	return 0;
}