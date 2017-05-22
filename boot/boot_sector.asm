; Boot Sector Code for the OS boot sector
; Author - Anish Sharma

[org 0x7c00]

mov [BOOT_DRIVE], dl
mov [0x7fe], byte dl

STAGE2 equ 0x800

STAGE2_SECTORS equ 2+1
TRACKS equ 2

mov [BOOT_DRIVE],dl

mov bp,0x9000
mov sp,bp

mov bx, msgReal
call print_string

call load_stage2

call STAGE2

jmp $

%include 'boot/bios.ASM'

[bits 16]
load_stage2:
	mov bx, msgStage2
	call print_string
	mov cl, 2
	mov bx, STAGE2
	mov dh, 1
	mov dl, [BOOT_DRIVE]
load_sector:
	call disk_load
	cmp cl, STAGE2_SECTORS
	je loaded
    cmp cl, 15
	add cl, 1
	add bx, 512
	jmp load_sector
loaded:
	ret

BOOT_DRIVE db 0
msgReal db "Booted in 16-bit mode",0
msgStage2 db "Loading the stage2 boot loader onto memory",0

times 510-($-$$) db 0
dw 0xaa55