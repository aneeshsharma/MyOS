/* Data Manipulation functions implementation
   File     -    dataman.c
   Author   -    Anish Sharma
 */
#include "dataman.h"
#include "stdint.h"

char getDigit(char x)
{
    if(x<10 && x>=0)
    {
        return (char) (x+'0');
    }
    else if(x>9)
    {
        return (char) ((x-10)+'A');
    }
    else
    {
        return (char) 0;
    }
}

int intLen(uint32_t x, short base)
{
    int i=0;
    while(x>0)
    {
        x/=base;
        i++;
    }
    return i-1;
}

int strLen(char* x)
{
    char r=1;
    int i=0;
    while(r!=0)
    {
        r = *x;
        i++;
    }
    return i-1;
}

char * itoa( int value, char * str, int base )
{
    char * rc;
    char * ptr;
    char * low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

void memset(uint8_t* addr, uint8_t data, uint32_t length)
{
    uint32_t i = 0;
    for(i=0;i<length;i++)
        *addr++ = data;
}