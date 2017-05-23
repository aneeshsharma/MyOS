/* Physical Memory manager declarations 
   File 	-	physmm.h
   Author	-	Anish Sharma
*/
 
#ifndef __PHYSMM_H
#define __PHYSMM_H

#include <stdint.h>

#define KERNEL_BASE 0x1000
#define KERNEL_LENGTH 15888

#define NUM_REGIONS 10
#define BLOCK_SIZE 4096

void get_mem_details(void);

void initialize_physmm(void);

void set_block(uint32_t block_num);
void clear_block(uint32_t block_num);
void set_region(uint32_t low, uint32_t high);
void clear_region(uint32_t low, uint32_t high);

uint8_t get_block(uint32_t block_num);

int32_t get_first_free_block(void);

inline uint32_t get_mem_blocks(void);
inline uint32_t get_reserved_blocks(void);
inline uint32_t get_free_blocks(void);

uint8_t* malloc(void);
uint8_t dump(uint8_t* block);
 
#endif