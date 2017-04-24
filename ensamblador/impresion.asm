section .data
	base db 10

section .bss
	cociente resb 1
	resto resb 1
	temp resb 1
	resultado resb 1

section .text
	GLOBAL _start

_start:
	mov esi,0
	mov al,254
	mov [cociente],al
	loop_num:
		mov al,[cociente]
		mov bl,[base]
		div bl
		mov [cociente],al
		mov [resto],ah
			call guardar
		mov cl,[cociente]
		cmp cl,0	
	jne loop_num

	loop_imprimir:
		dec esi
		mov eax,dword[resultado+esi]
		mov [temp],eax

		mov eax,4
		mov ebx,1
		mov ecx,temp
		mov edx,1
			int 80h

		cmp esi,0
	jne loop_imprimir

	mov rax,1
	mov rbx,0
		int 80h

	guardar:
		mov eax,[resto]
		add eax,'0'
		mov dword[resultado+esi],eax
		inc esi
	ret