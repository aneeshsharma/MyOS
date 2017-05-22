/* Defination for color codes in 32-bit mode 
   File 	-	colors.h
   Author	-	Anish Sharma
 */

#include "stdint.h"

#ifndef __COLORS_H
#define __COLORS_H

#define	BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHTGRAY 0x7

#define	DARKGRAY 0x8
#define B_BLUE 0x9
#define B_GREEN 0xA
#define B_CYAN 0xB
#define B_RED 0xC
#define B_MAGENTA 0xD
#define YELLOW 0xE
#define WHITE 0xF

uint8_t color(uint8_t fore, uint8_t bg);

uint8_t color(uint8_t fore, uint8_t bg) {
    return bg<<4|fore;
}

#endif
