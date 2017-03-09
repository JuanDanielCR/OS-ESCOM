section .data
	mensaje db "Incremento de 2 es: ",;0x0A salto linea, 0x0D retorno de carro1
	tamanio equ  $ -mensaje

	mdos db 0x0A, "Decremento de 4 es: ",
	tmdos equ $ -mdos

	mtres db 0x0A, "La suma de 2 y 3 es: "
	tmtres equ $ -mtres
section .bss
	resultado resb 1;variable temporal: n[ombre] resb [tamaño]
section .text
	global _start

;Primer mensaje
	_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, mensaje
	mov edx, tamanio
	int 80h
;Incremento (i++)
	mov eax, 0x02 ;reciclamos eax, le mandamos valor de 2
	inc eax		  ;incrementamos eax
	add eax, '0'  ;Imprimir con formato ASCII
	mov [resultado],eax  ;resultado no es un registro, usar [] solo en la asignación, envíar el valor del registro  nuestra variable tempora
;imprimir la variable temporal
	mov eax, 4
	mov ebx, 1
	mov ecx, resultado
	mov edx, 1 ;tamaño de nuestra variable a imprimir
	int 80h
;Segundo mensaje
	mov eax, 4
	mov ebx, 1
	mov ecx, mdos
	mov edx, tmdos
	int 80h
;Decremento
	mov eax, 0x04
	dec eax
	add eax, '0'
	mov [resultado], eax
;imprimir decremento
	mov eax, 4
	mov ebx, 1
	mov ecx, resultado
	mov edx, 1
	int 80h
;tercer mensaje
	mov eax, 4
	mov ebx, 1
	mov ecx, mtres
	mov edx, tmtres
	int 80h
;Suma
	mov eax, 0x02
	mov ebx, 0x03
	add eax, ebx
	add eax, '0'
	mov [resultado], eax
;imprimir
	mov eax, 4
	mov ebx, 1
	mov ecx, resultado
	mov edx, 1
	int 80h
;Fin del programa
	mov rax,1
	mov rbx,0
	int 80h 