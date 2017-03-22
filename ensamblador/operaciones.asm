section .data
	mensaje db "Incremento de 2 es: ";0x0A salto linea, 0x0D retorno de carro1
	tamanio equ  $ -mensaje

	mdos db 0x0A, "Decremento de 4 es: "
	tmdos equ $ -mdos

	msuma db 0x0A, "Suma de 2 y 3 es: "
	tmsuma equ $ -msuma

	mresta db 0x0A, "Resta de 5 y 1 es: "
	tmresta equ $ -mresta

	mprod db 0x0A, "Producto de 3 y 3 es: "
	tmprod equ $ -mprod

	mdiv db 0x0A, "División de 7 y 3 es: "
	tmdiv equ $ -mdiv

	mresiduo db 0x0A, " residuo: "
	tmresiduo equ $ -mresiduo

	mprod_signo db 0x0A, "Multiplicación de -4 y 2 es: "
	tmprod_signo equ $ -mprod_signo

section .bss
	resultado resb 1;variable temporal: n[ombre] resb [tamaño]
	residuo resb 1

	mult resb 4
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
	mov ecx, msuma
	mov edx, tmsuma
	int 80h
;Suma
	mov eax, 0x02
	mov ebx, 0x03
	add eax, ebx
	add eax, '0'
	mov [resultado], eax
;imprimir suma
	mov eax, 4
	mov ebx, 1
	mov ecx, resultado
	mov edx, 1
	int 80h
;Mensaje 4
	mov eax, 4
	mov ebx, 1
	mov ecx, mresta
	mov edx, tmresta
	int 80h
;Resta
	mov eax, 0x05
	mov ebx, 0x01
	sub eax, ebx
	add eax, '0'
	mov[resultado], eax
;imprimir resultado
	mov eax, 4
	mov ebx, 1
	mov ecx, resultado
	mov edx, 1
	int 80h
;Mensaje 5
	mov eax, 4
	mov ebx, 1
	mov ecx, mprod
	mov edx, tmprod
	int 80h
;Multiplicación
	mov eax, 0x03
	mov ebx, 0x03
	mul ebx
	add eax, '0'
	mov [resultado], eax
;imprimir resultado
	mov eax, 4
	mov ebx, 1
	mov ecx, resultado
	mov edx, 1
	int 80h
;Mensaje 6
	mov eax, 4
	mov ebx, 1
	mov ecx, mdiv
	mov edx, tmdiv
	int 80h
;Divisón
	mov al, 0x07 ;registros de 8 bits
	mov bl, 0x03
	div bl
	add al, '0'
	add ah, '0' ; registro ah para el residuo
	mov [resultado], al
	mov [residuo], ah
;imprimir resultado
	mov eax,4
	mov ebx,1
	mov ecx,resultado
	mov edx,1
	int 80h
;imprimir residuo mensaje
	mov eax, 4 
	mov ebx, 1
	mov ecx, mresiduo
	mov edx, tmresiduo
	int 80h
;imprimir residuo
	mov eax, 4
	mov ebx, 1
	mov ecx, residuo
	mov edx, 1
	int 80h
;Mensaje 6
	mov eax, 4
	mov ebx, 1
	mov ecx, mprod_signo
	mov edx, tmprod_signo
	int 80h
;Multiplicación con signo
	mov eax, 2	; DL= -1
	mov ebx, -4	; AL = -66
	imul ebx
	add eax, '0'
	mov [resultado], eax
;resultado 
	mov eax,4
	mov ebx,1
	mov ecx,resultado
	mov edx,1
	int 80h
;Fin del programa
	mov rax,1
	mov rbx,0
	int 80h 