/* Header file defining constants for Interrupt Controller
 * File 	- PIC.h
 * Author 	- Anish Sharma
 */

#ifndef __PIC_H
#define __PIC_H

#include "stdint.h"

// PIC 1 Interrupts
#define		x86_PIC_IRQ_TIMER				0
#define		x86_PIC_IRQ_KEYBOARD			1
#define		x86_PIC_IRQ_SERIAL2				3
#define		x86_PIC_IRQ_SERIAL1				4
#define		x86_PIC_IRQ_PARALLEL2			5
#define		x86_PIC_IRQ_DISKETTE			6
#define		x86_PIC_IRQ_PARALLEL1			7
 
// PIC 2 Interrupts
#define		x86_PIC_IRQ_CMOSTIMER			0
#define		x86_PIC_IRQ_CGARETRACE			1
#define		x86_PIC_IRQ_AUXILIARY			4
#define		x86_PIC_IRQ_FPU					5
#define		x86_PIC_IRQ_HDC					6

// Command Word 2 bit masks
#define		x86_PIC_OCW2_MASK_L1			0b00000001		//Level 1 interrupt level
#define		x86_PIC_OCW2_MASK_L2			0b00000010		//Level 2 interrupt level
#define		x86_PIC_OCW2_MASK_L3			0b00000100		//Level 3 interrupt level
#define		x86_PIC_OCW2_MASK_EOI			0b00100000		//End of Interrupt command
#define		x86_PIC_OCW2_MASK_SL			0b01000000		//Select command
#define		x86_PIC_OCW2_MASK_ROTATE		0b10000000		//Rotation command

// Command Word 3 bit masks
#define		x86_PIC_OCW3_MASK_RIS			0b00000001
#define		x86_PIC_OCW3_MASK_RIR			0b00000010
#define		x86_PIC_OCW3_MASK_MODE			0b00000100
#define		x86_PIC_OCW3_MASK_SMM			0b00100000
#define		x86_PIC_OCW3_MASK_ESMM			0b01000000
#define		x86_PIC_OCW3_MASK_D7			0b10000000

// PIC 1 register port addresses
#define 	x86_PIC1_REG_COMMAND			0x20			// command register
#define 	x86_PIC1_REG_STATUS				0x20			// status register
#define 	x86_PIC1_REG_DATA				0x21			// data register
#define 	x86_PIC1_REG_IMR				0x21			// interrupt mask register (imr)
 
// PIC 2 register port addresses
#define 	x86_PIC2_REG_COMMAND			0xA0			// ^ see above register names
#define 	x86_PIC2_REG_STATUS				0xA0
#define 	x86_PIC2_REG_DATA				0xA1
#define 	x86_PIC2_REG_IMR				0xA1

// Initialization Control Word 1 bit masks
#define 	x86_PIC_ICW1_MASK_IC4			0b00000001		// Expect ICW 4 bit
#define 	x86_PIC_ICW1_MASK_SNGL			0b00000010		// Single or Cascaded
#define 	x86_PIC_ICW1_MASK_ADI			0b00000100		// Call Address Interval
#define 	x86_PIC_ICW1_MASK_LTIM			0b00001000		// Operation Mode
#define 	x86_PIC_ICW1_MASK_INIT			0b00010000		// Initialization Command

// Initialization Control Word 1 commands
#define 	x86_PIC_ICW1_IC4_EXPECT			0b00000001		//Use when setting x86_PIC_ICW1_MASK_IC4
#define 	x86_PIC_ICW1_IC4_NO				0b00000000
#define 	x86_PIC_ICW1_SNGL_YES			0b00000010		//Use when setting x86_PIC_ICW1_MASK_SNGL
#define 	x86_PIC_ICW1_SNGL_NO			0b00000000
#define 	x86_PIC_ICW1_ADI_CALLINT4		0b00000100		//Use when setting x86_PIC_ICW1_MASK_ADI
#define 	x86_PIC_ICW1_ADI_CALLINT8		0b00000000
#define 	x86_PIC_ICW1_LTIM_LT			0b00001000		//Use when setting x86_PIC_ICW1_MASK_LTIM
#define 	x86_PIC_ICW1_LTIM_ET			0b00000000
#define 	x86_PIC_ICW1_INIT_YES			0b00010000		//Use when setting x86_PIC_ICW1_MASK_INIT
#define 	x86_PIC_ICW1_INIT_NO			0b00000000

// Initialization Control Word 4 bit masks
#define 	x86_PIC_ICW4_MASK_UPM			0b00000001		// Mode
#define 	x86_PIC_ICW4_MASK_AEOI			0b00000010		// Automatic EOI
#define 	x86_PIC_ICW4_MASK_MS			0b00000100		// Selects buffer type
#define 	x86_PIC_ICW4_MASK_BUF			0b00001000		// Buffered mode
#define 	x86_PIC_ICW4_MASK_SFNM			0b00010000		// Special fully-nested mode

// Initialization Control Word 4 commands
#define 	x86_PIC_ICW4_UPM_86MODE			0b00000001		//Use when setting x86_PIC_ICW4_MASK_UPM
#define 	x86_PIC_ICW4_UPM_MCSMODE		0b00000000
#define 	x86_PIC_ICW4_AEOI_AUTOEOI		0b00000010		//Use when setting x86_PIC_ICW4_MASK_AEOI
#define 	x86_PIC_ICW4_AEOI_NOAUTOEOI		0b00000000
#define 	x86_PIC_ICW4_MS_BUFFERMASTER	0b00000100		//Use when setting x86_PIC_ICW4_MASK_MS
#define 	x86_PIC_ICW4_MS_BUFFERSLAVE		0b00000000
#define 	x86_PIC_ICW4_BUF_MODEYES		0b00000000		//Use when setting x86_PIC_ICW4_MASK_BUF
#define 	x86_PIC_ICW4_BUF_MODENO			0b00000000
#define 	x86_PIC_ICW4_SFNM_NESTEDMODE	0b00010000		//Use when setting x86_PIC_ICW4_MASK_SFNM
#define 	x86_PIC_ICW4_SFNM_NOTNESTED		0b00000000

#define     PIC_EOI                         0x20

void x86_pic_send_command(uint8_t cmd, uint8_t picNum);
void x86_pic_send_data (uint8_t data, uint8_t picNum);
uint8_t x86_pic_read_data (uint8_t picNum);
void x86_pic_initialize(uint8_t base0, uint8_t base1);

#endif