; File containing Interrupt Routines and Routines Needed for interrupt Initialization
; Author - Anish Sharma

global load_idt

extern _idtr

load_idt:
	lidt [_idtr]
	ret


global default_int

global isr0
global isr1
global isr3
global isr4
global isr5
global isr11
global pit_counter
global keyboard_int

extern x86_default_handler

extern ISR0
extern ISR1
extern ISR3
extern ISR4
extern ISR5
extern ISR11

extern x86_pit_irq
extern x86_keyboard

default_int:
	pusha
	call x86_default_handler
	popa
	iret

isr0:
	pusha
	call ISR0
    popa
	iret

isr1:
	pusha
	call ISR1
    popa
	iret

isr3:
	pusha
	call ISR3
    popa
	iret

isr4:
	pusha
	call ISR4
    popa
	iret

isr5:
	pusha
	call ISR5
    popa
	iret
    
isr11:
	pusha
	call ISR11
    popa
	iret

pit_counter:
	pusha
	cli
	call x86_pit_irq
	sti
	popa
	iret
    
keyboard_int:
    pusha
    cli
    call x86_keyboard
    sti
    popa
    iret