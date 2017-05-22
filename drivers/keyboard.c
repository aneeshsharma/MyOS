/* Implementation of keyboard driver functions 
   File 	-	keyboard.h
   Author	-	Anish Sharma
 */
 
 #include "stdint.h"
 #include "keyboard.h"
 #include "../HALx86/misc.h"
 
 uint8_t scancode = 0;
 
 void print_menu(uint8_t n);
 int8_t menu_item = 1;
 
 void x86_keyboard(){
    
    scancode = byteIn(KEYBOARD_PORT);
    switch(scancode){
        case 0x1c:
            switch(menu_item){
                case 1:
                    clrscr();
                    print_help();
                    menu_item = -1;
                    break;
                case 2:
                    clrscr();
                    menu_item = -1;
                    break;
                case 3:
                    write_status("Shutdown not supported! Press the power button");
                    break;
            }
            break;
        case 0x53:
            clrscr();
            break;
        case 0x23:
            print("Hello");
            break;
        case 0x3b:
            print_help();
            break;
    }
    if(scancode >=2 && scancode <= 4){
        print_menu(scancode - 1);
        menu_item = scancode - 1;
    }
    x86_pic_sendEOI(1);
}