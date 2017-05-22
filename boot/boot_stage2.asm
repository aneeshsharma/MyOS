[org 0x800]

KERNEL equ 0x1000
KERNEL_SECTORS equ 30

mov dl, byte[0x7fe]
mov [BOOT_DRIVE], dl

mov bx, msgStage2
call print_string

call load_kernel

mov bx, msg
call print_string

mov [0x4ff], byte 0x00

int 0x12
jc memError
mov [0x500], ax

clc
mov ah, 0x88
int 0x15
jc memError
mov [0x502], ax

xor cx, cx
xor dx, dx
mov eax, 0x0000E801
int 0x15
jc memError
cmp ah, 0x86
je memError
cmp ah, 0x80
je memError
jcxz useax
mov eax, ecx
mov ebx, edx
useax:
mov [0x504], eax
mov [0x508], ebx

jmp memDone

memError:
    mov [0x4ff], byte 0xff
    
memDone:

mov bx, 0x7e0
mov es, bx
mov di, 0x0
call do_e820
mov bx, bp
mov [0x50C], bx

call switch_to_pm

%include 'boot/bios.ASM'

%include 'boot/gdt.ASM'
%include 'boot/protected_mode.ASM'
%include 'boot/print32.ASM'

[bits 16]

load_kernel:
	mov bx, msgKernel
	call print_string
    mov ax, 3
	mov cl, 4
    mov ch, 0
	mov bx, KERNEL
    mov dl, [BOOT_DRIVE]
    mov dh, 0
    mov ch, 0
load_sector:
    mov ah, 0x02
    mov al, 1
    int 0x13
    jc error1
    cmp al, 1
    jne error2
    push bx
    mov bl, [Sector]
    cmp bl, KERNEL_SECTORS
    pop bx
	je loaded
    push bx
    mov bl, [Sector]
    inc bl
    mov [Sector], bl
    pop bx
	inc cl
    cmp cl, 18
    jne continue
    add ch, 1
    mov cl, 1
continue:
	add bx, BytesPerSector
	jmp load_sector
loaded:
	ret
    
error1:
    mov bx, errorMsg1
    call print_string
    jmp $

error2:
    mov bx, errorMsg2
    call print_string
    jmp $
    
; use the INT 0x15, eax= 0xE820 BIOS function to get a memory map
; inputs: es:di -> destination buffer for 24 byte entries
; outputs: bp = entry count, trashes all registers except esi
do_e820:
	xor ebx, ebx		; ebx must be 0 to start
	xor bp, bp		; keep an entry count in bp
	mov edx, 0x0534D4150	; Place "SMAP" into edx
	mov eax, 0xe820
	mov [es:di + 20], dword 1	; force a valid ACPI 3.X entry
	mov ecx, 24		; ask for 24 bytes
	int 0x15
	jc short .failed	; carry set on first call means "unsupported function"
	mov edx, 0x0534D4150	; Some BIOSes apparently trash this register?
	cmp eax, edx		; on success, eax must have been reset to "SMAP"
	jne short .failed
	test ebx, ebx		; ebx = 0 implies list is only 1 entry long (worthless)
	je short .failed
	jmp short .jmpin
.e820lp:
	mov eax, 0xe820		; eax, ecx get trashed on every int 0x15 call
	mov [es:di + 20], dword 1	; force a valid ACPI 3.X entry
	mov ecx, 24		; ask for 24 bytes again
	int 0x15
	jc short .e820f		; carry set means "end of list already reached"
	mov edx, 0x0534D4150	; repair potentially trashed register
.jmpin:
	jcxz .skipent		; skip any 0 length entries
	cmp cl, 20		; got a 24 byte ACPI 3.X response?
	jbe short .notext
	test byte [es:di + 20], 1	; if so: is the "ignore this data" bit clear?
	je short .skipent
.notext:
	mov ecx, [es:di + 8]	; get lower uint32_t of memory region length
	or ecx, [es:di + 12]	; "or" it with upper uint32_t to test for zero
	jz .skipent		; if length uint64_t is 0, skip entry
	inc bp			; got a good entry: ++count, move to next storage spot
	add di, 24
.skipent:
	test ebx, ebx		; if ebx resets to 0, list is complete
	jne short .e820lp
.e820f:
	mov [mmap_ent], bp	; store the entry count
	clc			; there is "jc" on end of list to this point, so the carry must be cleared
	ret
.failed:
	stc			; "function unsupported" error exit
	ret


[bits 32]

BEGIN_PM:
	mov ebx, msgProt
	call print_string32
	call KERNEL
	jmp $

BytesPerSector equ 512
NumHeads equ 2
SectorsPerTrack equ 18

Sector db 0

mmap_ent dw 0

BOOT_DRIVE db 0

msgStage2 db "Stage 2 reched!", 0
msgProt db "Successfully switched to 32-bit mode",0
msgKernel db "Loading the kernel onto memory",0
msg db "Loaded!!", 0
errorMsg1 db "Error1", 0
errorMsg2 db "Error2", 0

times 1024-($-$$) db 0