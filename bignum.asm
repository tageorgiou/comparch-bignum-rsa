%define size 128
global add
global not
global inc
section .text
add:
	push ebp
	mov ebp,esp
	mov ebx,[ebp+8] ;a
	mov edx,[ebp+12] ;b 
	mov ecx,size
.loop:
	mov al,[ebx+ecx-1]
	adc al,[edx+ecx-1]
	mov [ebx+ecx-1],al
	loop .loop
	mov eax,ebx
	pop ebp
	ret
inc:
	push ebp
	mov ebp,esp
	mov ebx,[ebp+8] ;a
	mov ecx,size
	add byte [ebx+ecx-1],1
	dec ecx
.loop:
	mov al,[ebx+ecx-1]
	adc al,0
	mov [ebx+ecx-1],al
	loop .loop
	mov eax,ebx
	pop ebp
	ret
not:
	push ebp
	mov ebp,esp
	mov eax,[ebp+8]
	mov ecx,size
.loop:
	not byte [eax+ecx-1]
	loop .loop
	pop ebp
	ret
