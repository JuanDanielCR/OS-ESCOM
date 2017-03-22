section .data
	m1 db "Ingresa una cadena: ", 0x0A
	tm1 equ $ -m1

	m2 db "El numero introducido fue: ",0x0A
	tm2 equ $ -m2
section .bss
	cadena resb 5

section .text
	global _start

	_start:
;impresion del primer mensaje
	mov eax, 4
	mov ebx, 1
	mov ecx, m1
	mov edx, tm1
	int 80h
;lectura
	mov eax, 3 ;llamada al sistema para un lectura
	mov ebx, 2 ;std in 
	mov ecx, cadena
	mov edx, 5 
	int 80h
;impresion cadena leida
	mov eax, 4
	mov ebx, 1
	mov ecx, cadena
	mov edx, 5
	int 80h
; cerrar
;Fin del programa
	mov rax,
	
	mov rbx,0
	int 80h 