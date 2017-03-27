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
	mov rax, numero
	sub rax,'0' ; tomar valor decimal
	mov rcx, 10
	for:
		push rcx
		mul rcx
		add rax,'0'
		mov [resultado],rax
		

		mov rax, 4
		mov rbx, 1
		mov rcx, resultado
		mov rdx, 1
		
		int 80h
		mov rax, numero
		pop rcx
	loop for
	;fin
	mov rax,1
	mov rbx,0
	int 80h