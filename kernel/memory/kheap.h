#ifndef KHEAP_H
#define KHEAP_H

#include "../cpu/types.h"
#include "../../cathesimc/def.h"

u32 kmalloc_intrnl(size_t size, int align, u32* ph_addr);
u32 kmalloc_a(size_t size);
u32 kmalloc_p(size_t size, u32* ph_addr);
u32 kmalloc_ap(size_t size, u32* ph_addr);
u32 kmalloc(size_t size);

#endif

