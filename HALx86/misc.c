/* Implementing of some Miscellaneous Functions 
   File 	-	misc.c
   Author	-	Anish Sharma
 */

#include "stdint.h"

// delay for some time
void delay(uint32_t ms){
    uint64_t t1 = get_tick();
    uint64_t t2 = t1;
    while((t2-t1)<=ms){
        t2 = get_tick();
    }
}

void print_help(){
    clrscr();
    print("# HELP ##");
    print("MOS V2.0");
    print("Following Keyboard shortcuts supported:");
    print("- Del            -   clear the screen");
    print("- 'h'            -   print message \"Hello\"");
    print("- F1             -   Open help");
    print("- Any Number Key -   Open Menu");
}