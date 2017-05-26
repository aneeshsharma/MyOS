/* Physical Memory manager functions implementation
   File 	-	physmm.c
   Author	-	Anish Sharma
*/

#include "physmm.h"

// Structure defining a type to store Memory Map Entry
typedef struct {
    uint32_t base;
    uint32_t length;
    uint32_t type;
    uint32_t ext_attr;
}mmap_t;

mmap_t physmm_mmap[MAX_NUM_REGIONS];

uint16_t no_of_regions;

uint32_t no_mem_blocks;
uint32_t* mem_blocks;

uint32_t reserved;
uint32_t free;

uint32_t memoryKB;
uint16_t memoryMB;

void get_mem_details(void){
    if(*((uint8_t*) 0x4ff)==0xff){
        printC("Memory Not Recognized!!", 0x1c);
        return;
    }
    uint16_t conmB =  *((uint16_t*) 0x500);
    uint16_t extmB =  *((uint16_t*) 0x502);
    uint32_t mem1to16 = *((uint32_t*) 0x504);
    uint32_t memgreater16 = *((uint32_t*) 0x508);
    
    memoryKB = 1024 + mem1to16 + memgreater16*64;
    memoryMB = memoryKB/1024;
}

void initialize_physmm(void){
    uint32_t i=0, j=0;
    uint64_t y = 0;
    
    no_of_regions = *((uint16_t*)0x50c);
    
    get_mem_details();
    
    for(i=0; i < no_of_regions ; i++){
        physmm_mmap[i].base = (uint32_t) 0;
        physmm_mmap[i].length = (uint32_t) 0;
        physmm_mmap[i].type = (uint32_t) 0;
        physmm_mmap[i].ext_attr = (uint32_t) 0;
    }
    
    uint32_t* entry = (uint32_t*) 0x7e00;
    
    j=0;
    for(i=0; i < no_of_regions ; i++){
        physmm_mmap[i].base = (uint32_t) entry[j];
        physmm_mmap[i].length = (uint32_t) entry[j+2];
        physmm_mmap[i].type = (uint32_t) entry[j+4];
        physmm_mmap[i].ext_attr = (uint32_t) entry[j+5];
        j += 6;
    }
    
    no_mem_blocks = memoryKB/4;
    
    for(i=no_of_regions-1 ; i>=0 ; i--){
        if(physmm_mmap[i].type == 1){
            mem_blocks = (uint32_t*) physmm_mmap[i].base;
            for(i=0 ; i < no_mem_blocks/32 ; i++)
            {
                mem_blocks[i] = 0xffffffff;
            }
            reserved = no_mem_blocks;
            set_region(physmm_mmap[i].base, physmm_mmap[i].base + (no_mem_blocks/8) + 1);
            break;
        }
    }
    
    
    for(i = 0; i < no_of_regions-1; i++){
        if(physmm_mmap[i].type == 1){
            clear_region(physmm_mmap[i].base, physmm_mmap[i].base + physmm_mmap[i].length - 1);
        }
    }

	set_region(KERNEL_BASE, KERNEL_BASE + KERNEL_LENGTH);
}

void set_block(uint32_t block_num){
    uint32_t region = block_num / 32;
    uint8_t block = block_num % 32;
    mem_blocks[region] |= 1<<block;
    reserved++;
    free = no_mem_blocks - reserved;
}

void clear_block(uint32_t block_num){
    uint32_t region = block_num / 32;
    uint8_t block = block_num % 32;
    mem_blocks[region] &= ~(1<<block);
    reserved--;
    free = no_mem_blocks - reserved;
}

void set_region(uint32_t low, uint32_t high){
    uint32_t l = low/BLOCK_SIZE + ((low % BLOCK_SIZE==0)?0:1);
    uint32_t h = high/BLOCK_SIZE + ( (high % BLOCK_SIZE==0)?0:1);
    uint32_t i = 0;
    uint32_t diff = h-l;
    for(i=0 ; i < diff ; i++){
        set_block(l + i);
    }
}

void clear_region(uint32_t low, uint32_t high){
    uint32_t l = low/BLOCK_SIZE + ((low % BLOCK_SIZE==0)?0:1);
    uint32_t h = high/BLOCK_SIZE + ( (high % BLOCK_SIZE==0)?0:1);
    uint32_t i = 0;
    uint32_t diff = h-l;
    for(i=0 ; i < diff ; i++){
        clear_block(l + i);
    }
}

uint8_t get_block(uint32_t block_num){
    uint32_t region = block_num / 32;
    uint8_t block = block_num % 32;
    if(((mem_blocks[region]) & (1<<block))!=0)
        return 1;
    else
        return 0;
}

int32_t get_first_free_block(void){
    uint32_t i = 0, l = no_mem_blocks/32;
    for(i=0; i<l ; i++)
    {
        if(mem_blocks[i/32]!=0xffffffff){
            if(get_block(i)==0){
                return i;
            }
        }
    }
    return -1;
}

unsigned char* malloc(void){
    uint32_t free = get_first_free_block(), loc = 0;
    if(free==-1)
        return 0;
    
    loc = GET_ADDRESS(free);
    set_block(free);
    return (uint8_t*) loc;
}

unsigned char * malloc_bytes(uint32_t bytes)
{
	uint32_t no_blocks = bytes / BLOCK_SIZE + (bytes%BLOCK_SIZE == 0) ? 0 : 1;
	uint32_t l = no_mem_blocks / 32, i = 0, j = 0;
	uint32_t addr = 0;
	uint32_t n = no_blocks;
	for (i = 0; i<l; i++)
	{
		if (get_block(i) == 0) {
			j = i;
			n--;
		}
		else {
			n = no_blocks;
		}
		if (n == 0) {
			addr = GET_ADDRESS(j);
			set_region(addr, addr + no_blocks * BLOCK_SIZE);
			return (unsigned char*)addr;
		}
	}
	return 0;
}

uint8_t dump(unsigned char* addr){
    uint32_t loc = ((uint32_t) addr) / BLOCK_SIZE;
    clear_block(loc);
    return 0;
}

inline uint32_t get_mem_blocks(void){
    return no_mem_blocks;
}

inline uint32_t get_reserved_blocks(void){
    return reserved;
}

inline uint32_t get_free_blocks(void){
    return free;
}

inline uint16_t get_no_of_regions(void)
{
	return no_of_regions;
}
