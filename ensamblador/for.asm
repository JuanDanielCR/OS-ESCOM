section .data
	m1 db "Tabla de multiplicar",0x0A
	tm1 equ $ -m1
section .bss
	numero resb 1
	resultado resb 2

section .text
	global _start
	_start:

	mov eax,4
	mov ebx,1
	mov ecx,m1
	mov edx,tm1
	int 80h

	mov eax,3
	mov ebx,2
	mov ecx,numero
	mov edx, 1
	int 80h

	;for
	mov eax, numero
	sub eax,'0' ; tomar valor decimal
	mov ecx, 10
	for:
		push ecx
		mul ecx
		add eax,'0'
		mov [resultado],eax

		mov eax, 4
		mov ebx, 1
		mov cx, resultado
		mov edx, 1
		
		int 80h
		mov eax, numero
		pop ecx
	loop for
	;fin
	mov rax,1
	mov rbx,0
	int 80h