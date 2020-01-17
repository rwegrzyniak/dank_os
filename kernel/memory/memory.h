#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"
#include "../../cathesimc/def.h"
void memcpy(char* src, char* dst, unsigned int bytes);

void memset(u8* dest, u8 val, u32 len);

u32 kmalloc_intrnl(size_t size, short int align, u32* phys_addr);

u32 kmalloc(size_t size);
u32 kmalloc_a(size_t size);
u32 kmalloc_p(size_t size, u32* phys_addr);
u32 kmalloc_ap(size_t size, u32* phys_addr);

#endif
