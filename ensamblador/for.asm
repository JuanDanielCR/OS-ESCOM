section .data
	m1 db "Tabla de multiplicar",0x0A
	tm1 equ $ -m1
section .bss
	numero resb 1
	resultado resb 2

section .text
	global _start
	_start:

	mov rax,4
	mov rbx,1
	mov rcx,m1
	mov rdx,tm1
	int 80h

	mov rax,3
	mov rbx,2
	mov rcx,numero
	mov rdx, 1
	int 80h

	;for
	sub byte[numero],'0'

	;mov ah,1h
	;int 80h
	;mov [numero],ah

	mov rcx, 10
	for:
	;asginar valores a rcx y rax
		push rcx
		;mov rax,numero
		mov rax, 0x01
	;multiplicacion
		mul rcx
		add rax,'0'
		mov [resultado],rax
	;imprimir
		mov rax, 4
		mov rbx, 1
		mov rcx, resultado
		mov rdx, 1
		int 80h
	;pop	
		pop rcx
	loop for
	;fin
	mov rax,1
	mov rbx,0
	int 80h