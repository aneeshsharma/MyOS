; Functions for printing text on screen in 32-bit mode
; Author - Anish Sharma

[bits 32]

VIDEO_MEM equ 0xb8000
DEF_COLOR equ 0x0f

print_string32:
	pusha
	mov edx,VIDEO_MEM

print_string32_loop:
	mov al, [ebx]
	mov ah, DEF_COLOR

	cmp al,0
	je print_string32_end

	mov [edx],ax

	inc ebx
	add edx,2
	jmp print_string32_loop

print_string32_end:
	popa
	ret