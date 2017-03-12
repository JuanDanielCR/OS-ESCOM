										;fichero hello.asm
section .data							;Inicio de la sección datos, para datos inicializados
	mensaje db "Hola ensamblador", 10   ;El 10 en ensamblador representa el salto de linea o fin de cadena
	length equ $-mensaje    			;Ayuda a calcular el tamaño de la variable, con la palabra reservada equ

section .text							;Sección de código
	global _start	 					;Declaración de una variable global

	_start:								;Inicio del código
	;------Impresión en pantalla---------

	mov eax, 4							;mov registro_general,valor_enviado | mover (nombre registro),(DESCRIPTORES)
										;Table de descriptores: 4-llama a la funcion sys_write(), 1-referenciaa a la salida estándar stdout, 2-error
	mov ebx, 1							
	mov ecx, mensaje 					;Pone la dirección de la variable msg en el registro ebx
	mov edx, length 					;Pone la longitud del mensaje incluido
	int 80h								;Interrupción, al lanzarse se ejecuta el código, llama al OS

	;Final del programa
	mov rax,1							;1 en rax- exit
	mov rbx,0 							;0 salida standar
	int 80h