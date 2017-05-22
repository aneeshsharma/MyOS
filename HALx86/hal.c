/* Hardware Abstraction Layer function implementations 
   File 	-	hal.c
   Author	-	Anish Sharma
 */

#include "hal.h"
#include "idt.h"
#include "pit.h"
#include "../drivers/keyboard.h"

void hal_initialize(){
	x86_idt_initialize(0x8);
	
    install_exceptions(0x8);
	
    x86_pic_initialize(32,40);
    x86_pit_initialize(32,0x8);
	x86_pit_start_counter(1000,x86_PIT_OCW_COUNTER_0, x86_PIT_OCW_MODE_SQUAREWAVEGEN);
    install_interrupts(0x8);
    
    x86_pic_mask_all();
    x86_pic_clear_mask(0);
    x86_pic_clear_mask(1);
    enable();
	return;
}

inline void enable(){
	asm("sti");
	return;
}
inline void disable(){
	asm("cli");
	return;
}

void install_exceptions(uint16_t codeSel){
	x86_install_IR(0, x86_IDT_DESC_PRESENT | x86_IDT_DESC_BIT32, codeSel, isr0);
	x86_install_IR(1, x86_IDT_DESC_PRESENT | x86_IDT_DESC_BIT32, codeSel, isr1);
	x86_install_IR(3, x86_IDT_DESC_PRESENT | x86_IDT_DESC_BIT32, codeSel, isr3);
	x86_install_IR(4, x86_IDT_DESC_PRESENT | x86_IDT_DESC_BIT32, codeSel, isr4);
	x86_install_IR(5, x86_IDT_DESC_PRESENT | x86_IDT_DESC_BIT32, codeSel, isr5);
    x86_install_IR(5, x86_IDT_DESC_PRESENT | x86_IDT_DESC_BIT32, codeSel, isr11);
}

void install_interrupts(uint16_t codeSel){
	x86_install_IR(33, x86_IDT_DESC_PRESENT | x86_IDT_DESC_BIT32, codeSel, keyboard_int);
}

void hal_shutdown(){
    disable();
}