/* Function implementations for Timer 
   File 	-	pit.c
   Author	-	Anish Sharma
 */

#include "pit.h"
#include "stdint.h"
#include "idt.h"

extern void pit_counter();

uint64_t pit_ticks = 56;

void x86_pit_irq() {
	pit_ticks++;
    x86_pic_sendEOI(0);
}

void x86_pit_send_command (uint8_t cmd) {
	byteOut(x86_PIT_REG_COMMAND, cmd);
}

void x86_pit_send_data(uint16_t data, uint8_t counter) {
	uint8_t	port= (counter==x86_PIT_OCW_COUNTER_0) ? x86_PIT_REG_COUNTER0 : ((counter==x86_PIT_OCW_COUNTER_1) ? x86_PIT_REG_COUNTER1 : x86_PIT_REG_COUNTER2);
 
	byteOut(port, data);
}

uint8_t x86_pit_read_data(uint16_t counter) {
 
	uint8_t	port= (counter==x86_PIT_OCW_COUNTER_0) ? x86_PIT_REG_COUNTER0 : ((counter==x86_PIT_OCW_COUNTER_1) ? x86_PIT_REG_COUNTER1 : x86_PIT_REG_COUNTER2);
 
	return byteIn(port);
}

void x86_pit_initialize(uint8_t irq, uint8_t irCodeSeg) {
 
	//! Install our interrupt handler
	x86_install_IR(irq, x86_IDT_DESC_PRESENT | x86_IDT_DESC_BIT32, irCodeSeg, pit_counter);
}

void x86_pit_start_counter (uint32_t freq, uint8_t counter, uint8_t mode) {
 
	if(freq==0)
		return;
 
	uint16_t divisor = 1193180 / freq;
 
	//! send operational command
	uint8_t ocw=0;
	ocw = (ocw & ~x86_PIT_OCW_MASK_MODE) | mode;
	ocw = (ocw & ~x86_PIT_OCW_MASK_RL) | x86_PIT_OCW_RL_DATA;
	ocw = (ocw & ~x86_PIT_OCW_MASK_COUNTER) | counter;
	x86_pit_send_command (ocw);
 
	//! set frequency rate
	x86_pit_send_data (divisor & 0xff, 0);
	x86_pit_send_data ((divisor >> 8) & 0xff, 0);
 
	//! reset tick count
	pit_ticks=0;
}

inline uint32_t get_tick(){
	return pit_ticks;
}