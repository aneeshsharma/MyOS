/* Implementations for interrupt initialization and installing IRQs 
   File 	-	int86.c
   Author	-	Anish Sharma
 */

#include "idt.h"

void idt_install(){
	load_idt();
}

int_handler x86_default_handler(){
	#ifdef DEBUG
		write_status("An Unhandled Exception Occured!! Default Handler Called.");
	#else
        clrscr();
        print("Fatal Error : An Unhandled Exception Occured! OS has crashed");
		while(1);
	#endif
	return;
}

uint8_t x86_install_IR(uint8_t i, uint16_t flags, uint16_t sel, uint32_t uiBase){
	if(i>MAX_INTERRUPTS)
		return 0;
	if(!uiBase)
		return 0;
 
	_idt[i].baseLo		=	uiBase & 0xffff;
	_idt[i].baseHi		=	(uiBase >> 16) & 0xffff;
	_idt[i].reserved	=	0;
	_idt[i].flags		=	flags;
	_idt[i].select		=	sel;
 
	return	0;
}

int x86_idt_initialize(uint16_t codeSel) {
	_idtr.limit = sizeof (struct idt) * MAX_INTERRUPTS -1;
	_idtr.base	= (uint32_t)(&_idt[0]);
 	int i = 0;
	//! null out the idt
	memset((struct idt*)&_idt[0], 0, sizeof(struct idt) * MAX_INTERRUPTS);
 
	//! register default handlers
	for (i=0; i<MAX_INTERRUPTS; i++)
		x86_install_IR(i, x86_IDT_DESC_PRESENT | x86_IDT_DESC_BIT32, codeSel, (uint32_t)(default_int));
 
	//! install our idt
	idt_install();
 
	return 0;
}

void geninterrupt () {
	asm("int $5");
}

void enableInt(){
	asm("sti");
}