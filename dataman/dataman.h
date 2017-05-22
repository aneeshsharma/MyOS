/* Data Manipulation function declarations 
   File 	-	dataman.h
   Author	-	Anish Sharma
 */

#include "stdint.h"

#ifndef __DATA_MAN_
#define __DATA_MAN_

char getDigit(char x);

int intLen(uint32_t x, short base);

int strLen(char* x);

char * itoa( int value, char * str, int base );

#endif