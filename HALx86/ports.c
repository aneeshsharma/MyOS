/* Functions for handling low level Input & Outputs 
   File 	-	ports.c
   Author	-	Anish Sharma
 */

#include "ports.h"

//Function to read a byte from a port
unsigned char byteIn(unsigned short port) {
	unsigned char result;
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}

//Function to output a byte to a port
void byteOut(unsigned short port, unsigned short data) {
	__asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

//Function to read a word from a port
unsigned short wordIn(unsigned short port) { 
	unsigned short result;
	__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
	return result;
}

//Function to output a word to a port
void wordOut(unsigned short port , unsigned short data) {
	__asm__("out %%ax, %%dx" : :"a" (data), "d" (port));
}