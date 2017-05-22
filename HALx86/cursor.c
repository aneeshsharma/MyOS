/* Cursor operation function implementations 
   File 	-	cursor.c
   Author	-	Anish Sharma
 */

void update_cursor(int col, int row)
{
    unsigned short position=(row*80) + col;

    byteOut(0x3D4, 0x0F);
    byteOut(0x3D5, (unsigned char)(position&0xFF));

    byteOut(0x3D4, 0x0E);
    byteOut(0x3D5, (unsigned char )((position>>8)&0xFF));
}