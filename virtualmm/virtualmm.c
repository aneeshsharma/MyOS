#include "virtualmm.h"

inline void pte_add_attribute(pt_entry * e, uint32_t attr)
{
	*e |= attr;
}

inline void pte_del_attribute(pt_entry * e, uint32_t attr)
{
	*e &= ~(attr);
}

inline void pte_set_frame(pt_entry * e, uint8_t * addr)
{
	*e = x86_PTE_FRAME | (((uint32_t) addr)<<12);
}

inline uint8_t pte_is_present(pt_entry * e)
{
	if ((*e & ((uint32_t)1)) == 0)
		return 0;
	else
		return 1;
}

inline uint8_t pte_is_writable(pt_entry * e)
{
	if ((*e & ((uint32_t) 0b10)) == 0)
		return 0;
	else
		return 1;
}

inline uint32_t pte_frame_address(pt_entry * e)
{
	return (*e >> 12);
}
