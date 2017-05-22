/* Hardware Abstraction Layer function declarations 
   File 	-	hal.h
   Author	-	Anish Sharma
 */
#include "stdint.h"
#include "isr_decl.h"


#ifndef __HAL_H
#define __HAL_H

// HAL initialization
void hal_initialize();

// Function that installs software exceptions
void install_exceptions(uint16_t codeSel);

// Functions to enable and disable interrupts
inline void enable();
inline void disable();

// Function that installs hardware interrupts
void install_interrupts(uint16_t codeSel);

#endif