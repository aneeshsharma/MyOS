/* The Main Kernel code 
   File     -  kernel.c     
   Author   -  Anish Sharma
 */

#include <stdint.h>
#include <stddef.h>
#include "../physmm/physmm.h"

extern memoryMB;

void print_menu(uint8_t n);

void main()
{
    /*Declarations*/
    #ifdef DEBUG
        char* status = "MOS V2.0 Copyright 2017 | Welcome Anish Sharma | Development Build";
    #else
        char* status = "Welcome Anish Sharma";
    #endif
    
    uint16_t i = 0;
    
    hal_initialize();
    
    initialize_physmm();

	clrscr();
    print("Number of Blocks:");

    
    print("Reserved B:");
    
    uint8_t* x = malloc();
    print("X reserved a block");
    uint8_t* y = malloc();
    delay(1000);
    dump(y);
    print("Y reserved a block");
    
    print("Free Blocks:");
    
    print("First Free Block:");
    
    print("Memory (in MB):");

	write_status(status);

	while(1) {
		if (get_tick() % 1000 == 0)
			print("Tick");
	}
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
