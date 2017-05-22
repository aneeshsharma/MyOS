/* Function declarations for low level I/O 
   File 	-	ports.h
   Author	-	Anish Sharma
 */

#ifndef __PORTS_H
#define __PORTS_H

unsigned char byteIn(unsigned short port);
void byteOut(unsigned short port, unsigned short data);
unsigned short wordIn(unsigned short port);
void wordOut(unsigned short port , unsigned short data);

#endif