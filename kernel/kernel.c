/* The Main Kernel code 
   File     -  kernel.c     
   Author   -  Anish Sharma
 */

#include <stdint.h>
#include <stddef.h>
#include "../physmm/physmm.h"

extern memoryMB;

void print_menu(uint8_t n);

uint64_t x[1000];

void main()
{
    /*Declarations*/
    #ifdef DEBUG
        char* status = "MOS V2.0 Copyright 2017 | Welcome Anish Sharma | Development Build";
    #else
        char* status = "Welcome Anish Sharma";
    #endif
    
    uint16_t i = 0;
    
    for(i=0;i<1000;i++)
        x[i] = 0;
    
    fillScreen();
    
    hal_initialize();
    
    initialize_physmm();
    
    print("Number of Blocks:");
    printfNum(get_mem_blocks(), 10);
    
    print("Reserved Blocks:");
    printfNum(get_reserved_blocks(), 10);
    
    uint8_t* x = malloc();
    print("X reserved a block");
    uint8_t* y = malloc();
	print("Y reserved a block");
    delay(1000);
    dump(y);
	print("Y deleted a block");
    
    print("Free Blocks:");
    printfNum(get_free_blocks(), 10);
    
    print("First Free Block:");
    printfNum(get_first_free_block(), 16);
    
    print("Memory (in MB):");
    printfNum(memoryMB, 10);    
    write_status(status);
}

void print_menu(uint8_t n){
    clrscr();
    print("");
    print("");
    print("");
    print("");
    print("");
    write_string_line(0x1e, "Welcome to MOS V2.0! Below is the menu. Open up help to start.", 0);
    write_string_line(0x1e, "MENU - Press a number to select the option", 1);
    write_string_line((n==1)?0x30:0x1f, "1. Help", 2);
    write_string_line((n==2)?0x30:0x1f, "2. Clear", 3);
    write_string_line((n==3)?0x30:0x1f, "3. Shutdown", 4);
}
