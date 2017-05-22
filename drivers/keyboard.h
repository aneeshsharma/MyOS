/* Declaration of keyboard driver functions
   File 	-	misc.h
   Author	-	Anish Sharma
 */
 
 #ifndef __KEYBOARD_H
 #define __KEYBOARD_H
 
 #define KEYBOARD_PORT 0x60
 
 extern void keyboard_int();
 
 void x86_keyboard();
 
 #endif