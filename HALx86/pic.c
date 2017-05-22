/* PIC control implementations 
   File 	-	File Name
   Author	-	Anish Sharma
 */

#include "pic.h"
#include "stdint.h"
#include "misc.h"

void x86_pic_send_command(uint8_t cmd, uint8_t picNum) {
 
	if (picNum > 1)
		return;
 
	uint8_t	reg = (picNum==1) ? x86_PIC2_REG_COMMAND : x86_PIC1_REG_COMMAND;
	byteOut(reg, cmd);
}

void x86_pic_send_data (uint8_t data, uint8_t picNum) {
	if (picNum > 1)
		return;
 
	uint8_t	reg = (picNum==1) ? x86_PIC2_REG_DATA : x86_PIC1_REG_DATA;
	byteOut(reg, data);
}

uint8_t x86_pic_read_data (uint8_t picNum) {
 
	if (picNum > 1)
		return 0;
 
	uint8_t	reg = (picNum==1) ? x86_PIC2_REG_DATA : x86_PIC1_REG_DATA;
	return byteIn(reg);
}

void x86_pic_initialize(uint8_t base0, uint8_t base1) {
	uint8_t		icw	= 0;
 
	//! Begin initialization of PIC
 
	icw = (icw & ~x86_PIC_ICW1_MASK_INIT) | x86_PIC_ICW1_INIT_YES;
	icw = (icw & ~x86_PIC_ICW1_MASK_IC4) | x86_PIC_ICW1_IC4_EXPECT;
	x86_pic_send_command (icw, 0);
	x86_pic_send_command (icw, 1);
 
	//! Send initialization control word 2. This is the base addresses of the irq's
	x86_pic_send_data (base0, 0);
	x86_pic_send_data (base1, 1);
 
	//! Send initialization control word 3. This is the connection between master and slave.
	//! ICW3 for master PIC is the IR that connects to secondary pic in binary format
	//! ICW3 for secondary PIC is the IR that connects to master pic in decimal format
 
	x86_pic_send_data (0x04, 0);
	x86_pic_send_data (0x02, 1);
 
	//! Send Initialization control word 4. Enables x86 mode
 
	icw = (icw & ~x86_PIC_ICW4_MASK_UPM) | x86_PIC_ICW4_UPM_86MODE;
	x86_pic_send_data (icw, 0);
	x86_pic_send_data (icw, 1);
}

void x86_pic_sendEOI(unsigned char irq)
{
	if(irq >= 8)
        byteOut(x86_PIC2_REG_COMMAND, PIC_EOI);
	byteOut(x86_PIC1_REG_COMMAND, PIC_EOI);
}

uint8_t x86_pic_set_mask(uint8_t irq){
    uint8_t pic = 0;
    if(irq>=8){
        pic = 1;
    }
    if(irq>15)
        return -1;
    uint8_t data = x86_pic_read_data(pic);
    data |= 1<<irq;
    x86_pic_send_data(data, pic);
}

uint8_t x86_pic_clear_mask(uint8_t irq){
    uint8_t pic = 0;
    if(irq>=8){
        pic = 1;
    }
    if(irq>15)
        return -1;
    uint8_t data = x86_pic_read_data(pic);
    data &= ~(1<<irq);
    x86_pic_send_data(data, pic);
}

void x86_pic_mask_all(){
    x86_pic_send_data(0xff, 0);
    x86_pic_send_data(0xff, 1);
}