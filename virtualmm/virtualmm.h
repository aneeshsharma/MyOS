#ifndef __VIRTUALMM_H
#define __VIRTUALMM_H

#include "stdint.h"

enum PAGE_PTE_FLAGS {

	x86_PTE_PRESENT = 1,		//0000000000000000000000000000001
	x86_PTE_WRITABLE = 2,		//0000000000000000000000000000010
	x86_PTE_USER = 4,		//0000000000000000000000000000100
	x86_PTE_WRITETHOUGH = 8,		//0000000000000000000000000001000
	x86_PTE_NOT_CACHEABLE = 0x10,		//0000000000000000000000000010000
	x86_PTE_ACCESSED = 0x20,		//0000000000000000000000000100000
	x86_PTE_DIRTY = 0x40,		//0000000000000000000000001000000
	x86_PTE_PAT = 0x80,		//0000000000000000000000010000000
	x86_PTE_CPU_GLOBAL = 0x100,		//0000000000000000000000100000000
	x86_PTE_LV4_GLOBAL = 0x200,		//0000000000000000000001000000000
	x86_PTE_FRAME = 0x7FFFF000 	//1111111111111111111000000000000
};

enum PAGE_PDE_FLAGS {

	I86_PDE_PRESENT = 1,		//0000000000000000000000000000001
	I86_PDE_WRITABLE = 2,		//0000000000000000000000000000010
	I86_PDE_USER = 4,		//0000000000000000000000000000100
	I86_PDE_PWT = 8,		//0000000000000000000000000001000
	I86_PDE_PCD = 0x10,		//0000000000000000000000000010000
	I86_PDE_ACCESSED = 0x20,		//0000000000000000000000000100000
	I86_PDE_DIRTY = 0x40,		//0000000000000000000000001000000
	I86_PDE_4MB = 0x80,		//0000000000000000000000010000000
	I86_PDE_CPU_GLOBAL = 0x100,		//0000000000000000000000100000000
	I86_PDE_LV4_GLOBAL = 0x200,		//0000000000000000000001000000000
	I86_PDE_FRAME = 0x7FFFF000 	//1111111111111111111000000000000
};

typedef uint32_t pt_entry;
typedef uint32_t pd_entry;

inline void pte_add_attribute(pt_entry* e, uint32_t attr);
inline void pte_del_attribute(pt_entry* e, uint32_t attr);
inline void pte_set_frame(pt_entry* e, uint8_t* addr);
inline uint8_t pte_is_present(pt_entry* e);
inline uint8_t pte_is_writable(pt_entry* e);
inline uint32_t pte_frame_address(pt_entry* e);

#endif