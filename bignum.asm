%define size 8
global add
section .text
add:
	push ebp
	mov ebp,esp
	mov ebx,[ebp+8] ;a
	mov edx,[ebp+12] ;b 
	mov al,[ebx+7]
	add al,[edx+7]
	mov [ebx+7],al

	mov al,[ebx+6]
	adc al,[edx+6]
	mov [ebx+6],al

	mov eax,ebx
	
	pop ebp
	ret
