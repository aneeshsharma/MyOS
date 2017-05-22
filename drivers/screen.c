/* Screen driver function implementations
   File     -    screen.c
   Author    -    Anish Sharma
 */

#include "screen.h"
#include "colors.h"
#include "stdint.h"

uint8_t __c_line = 0;

void write_string( unsigned char colour, const unsigned char *string ) {
    volatile unsigned char *vid = (unsigned char*) VIDEO_MEM;
    while(*string != 0)
    {
        *(vid) = *string;
        *(vid+1) = colour;
        ++string;
        vid+=2;
    }
}

void write_string_line( unsigned char colour, const unsigned char *string, uint8_t pos ) {
    volatile unsigned char *vid = (unsigned char*) VIDEO_MEM;
    int p = 1;
    vid+=pos*160;
    while(*string != 0)
    {
        *vid = *string;
        *(vid+1) = colour;
        ++string;
        vid+=2;
    }

}

void write_string_pos( unsigned char colour, const unsigned char *string, uint8_t col, uint8_t row) {
    volatile unsigned char *vid = (unsigned char*) VIDEO_MEM;
    vid+=2*((row*80)+col);
    while(*string != 0)
    {
        *vid = *string;
        *(vid+1) = colour;
        ++string;
        vid+=2;
    }

}

void putChar(unsigned char character, uint8_t col, uint8_t row, uint8_t attr) {
    volatile unsigned char* vid_mem = (unsigned char *) VIDEO_MEM;
    int offset = (row*80 + col)*2;
    vid_mem += offset;
    if(!attr) {
        attr = default_color;
    }
    *(unsigned short int *)vid_mem = (attr<<8)+character;
}

void clrscr()
{
	volatile unsigned char* vid = (unsigned char *) VIDEO_MEM;
	uint16_t i=0, limit = 80*(MAX_LINES+1);
    for (i = 0; i < limit; i++)
    {
        *vid = ' ';
        *(vid+1) = default_color;
        vid += 2;
    }
    __c_line=0;
}

void printDigit(uint8_t x, uint8_t col, uint8_t row, uint8_t attr)
{
    volatile unsigned char* vid_mem = (unsigned char *) VIDEO_MEM;
    uint16_t offset = (row*80 + col)*2;
    vid_mem += offset;
    if(!attr) {
        attr = default_color;
    }
    if(x>=0 && x<=9)
    	*(uint16_t *)vid_mem = (attr<<8)+(x+0x30);
}

void printNum(uint32_t x, uint8_t col, uint8_t row, uint8_t attr,uint8_t base)
{
    if(x==0)
        putChar('0',col,row,attr);
    else{
        col += (short) intLen(x,base);
        while(x>0)
        {
            putChar(getDigit((x%base)),col,row,attr);
            col--;
            x/=base;
        }
    }
}

void printHex(uint32_t x, uint8_t col, uint8_t row, uint8_t attr)
{
    write_string_pos(attr,"0x",col,row);
    printNum(x,col+2,row,attr,16);
}

void shiftUp()
{
    volatile unsigned char *vid = (unsigned char*) VIDEO_MEM;
    int ii = 0, limit = 80*MAX_LINES;
    while(ii<limit)
    {
        *vid = *(vid+160);
        *(vid+1) = *(vid+161);
        vid+=2;
        ii++;
    }
    short i = 0;
    for(i=0;i<80;i++)
        putChar(' ',i,MAX_LINES,default_color);
}

void print(unsigned char* str){
    volatile unsigned char *vid = (unsigned char*) VIDEO_MEM;
    if(__c_line>MAX_LINES){
        shiftUp();
        __c_line = MAX_LINES;
    }
    int pos = 0;
    vid += __c_line*160;
    while(*str != 0)
    {
        *(vid) = *str;
        *(vid+1) = default_color;
        ++str;
        vid+=2;
        pos++;
        if(pos>79)
            __c_line += 1;
    }
    __c_line +=1;
}


void printC(unsigned char* str, uint8_t color){
    volatile unsigned char *vid = (unsigned char*) VIDEO_MEM;
    if(__c_line>MAX_LINES){
        shiftUp();
        __c_line = MAX_LINES;
    }
    int pos = 0;
    vid += __c_line*160;
    while(*str != 0)
    {
        *(vid) = *str;
        *(vid+1) = color;
        ++str;
        vid+=2;
        pos++;
        if(pos>79)
            __c_line += 1;
    }
    __c_line +=1;
}

void write_status(unsigned char* status){
    uint8_t i = 0;
    for(i=0;i<80;i++)
        putChar(' ',i,24,STATUS_COLOR);
    write_string_line(STATUS_COLOR,status,24);
}