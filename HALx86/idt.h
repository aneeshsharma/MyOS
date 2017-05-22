/* Some functions and constants for Interrupts Initialization 
   File 	-	idt.h
   Author	-	Anish Sharma
 */

#include "stdint.h"

#ifndef __IDT_H
#define __IDT_H

#define MAX_INTERRUPTS 256

#define x86_IDT_DESC_BIT16		0b00000110
#define x86_IDT_DESC_BIT32		0b00001110
#define x86_IDT_DESC_RING0		0b00000000
#define x86_IDT_DESC_RING1		0b01000000
#define x86_IDT_DESC_RING2		0b00100000
#define x86_IDT_DESC_RING3		0b01100000
#define x86_IDT_DESC_PRESENT	0b10000000

struct __attribute__((packed)) idt{
    uint16_t baseLo;
    uint16_t select;
    uint8_t reserved;
    uint8_t flags;
    uint16_t baseHi;
};

struct __attribute__((packed)) idtr {
    uint16_t limit;
    uint32_t base;
};

struct idt _idt[MAX_INTERRUPTS];

#define idtADDR &_idt[0]

struct idtr _idtr;

extern void load_idt();
extern void default_int();

typedef void (*int_handler)(void);

#endif