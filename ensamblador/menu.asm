section .data
	m1 db 0x0A,"----Menu----", 0x0A
	tm1 equ $ -m1
	m2 db "1. Suma", 0x0A
	tm2 equ $ -m2
	m3 db "2. Resta", 0x0A
	tm3 equ $ -m3 
	m4 db "3. Multiplicacion", 0x0A
	tm4 equ $ -m4
	m5 db "4. Division", 0x0A
	tm5 equ $ -m5
	m6 db "5. Multiplicacion signo", 0x0A
	tm6 equ $ -m6
	m7 db "6. Division signo", 0x0A
	tm7 equ $ -m7
	m8 db "Numero: ",0x0A
	tm8 equ $ -m8
section .bss
	cadena resb 1
	resultado resb 5
	residuo resb 1
	n1 resb 2
	n2 resb 2
section .text
	global _start

	_start:
	;impresion m1
	mov eax, 4
	mov ebx, 1
	mov ecx, m1
	mov edx, tm1
	int 80h
	;impresion m2
	mov eax, 4
	mov ebx, 1
	mov ecx, m2
	mov edx, tm2
	int 80h
	;impresion m3
	mov eax, 4
	mov ebx, 1
	mov ecx, m3
	mov edx, tm3
	int 80h
	;impresion del primer mensaje
	mov eax, 4
	mov ebx, 1
	mov ecx, m4
	mov edx, tm4
	int 80h
	;impresion del primer mensaje
	mov eax, 4
	mov ebx, 1
	mov ecx, m5
	mov edx, tm5
	int 80h


	;lectura
	mov eax, 3 ;llamada al sistema para un lectura
	mov ebx, 2 ;std in 
	mov ecx, cadena
	mov edx, 5 
	int 80h

	cmp byte[cadena],byte '1'
		je suma

	cmp byte[cadena],byte '2'
		je resta

	cmp byte[cadena],byte '3'
		je mult

	cmp byte[cadena],byte '4'
		je divi
	;Etiquetas
suma:
	;Suma
	mov eax, 1
	mov ebx, 2
	add eax, ebx
	add eax, '0'
	mov [resultado], eax
	;imprimir suma
	mov eax, 4
	mov ebx, 1
	mov ecx, resultado
	mov edx, 1
	int 80h
	;regreso
	jmp _start

resta:
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
	;regreso
	jmp _start
mult:
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
	;regreso
	jmp _start
divi:
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
	jmp _start
	;fin
	mov rax,1
	mov rbx,0
	int 80h