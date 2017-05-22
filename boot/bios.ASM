; Real Mode Functions for Interfacing with BIOS
; Author - Anish Sharma

[bits 16]

print_string:
	pusha
	mov cx,bx
	mov ah,0x0e
	printStringStart:
	mov al,[bx]
	cmp al,0
	je done
	int 0x10
	inc bx
	jmp printStringStart
	done:
	popa
	ret

disk_load:
	pusha
	push dx
	mov ah,0x02
	mov al,dh
    mov dh,0x0
	int 0x13
	jc disk_error
	pop dx
	cmp dh,al
	jne disk_error
	popa
	ret

disk_error:
	mov ah,0x0e
	mov al,'X'
	int 0x10
	mov bx,errMsg
	call print_string
	jmp $

errMsg:
	db "Disk Read Error....."
	times 80-20 db " "
	db 0