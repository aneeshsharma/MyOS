/* Screen driver functions declarations and some constants 
   File 	-	screen.c
   Author	-	Anish Sharma
 */

#ifndef __SCREEN_DRIVERS__
#define __SCREEN_DRIVERS__

#include "stdint.h"

#define VIDEO_MEM 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define MAX_LINES 23

#define STATUS_COLOR 0x30

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

const uint8_t default_color = 0x1f;

void clrscr();

void write_string( unsigned char colour, const unsigned char *string );
void write_string_line( unsigned char colour, const unsigned char *string, uint8_t pos );
void write_string_pos( unsigned char colour, const unsigned char *string, uint8_t col, uint8_t row);

void putChar(unsigned char character, uint8_t col, uint8_t row, unsigned char attr);
void printDigit(uint8_t x, uint8_t col, uint8_t row, uint8_t attr);

void printNum(uint32_t x, uint8_t col, uint8_t row, uint8_t attr,uint8_t base);
void printHex(uint32_t x, uint8_t col, uint8_t row, uint8_t attr);

void print(unsigned char* str);
void printC(unsigned char* str, uint8_t color);

void write_status(unsigned char* status);

void shiftUp();

#endif
