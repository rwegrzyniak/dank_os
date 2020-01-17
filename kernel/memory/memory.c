#include "./memory.h"
#include "../cpu/types.h"
#include "../../cathesimc/def.h"


void memcpy(char* src, char* dst, unsigned int bytes){
		int i=0;
		for (i=0; i< bytes; i++){
				dst[i] = src[i];
		
		}
}

void memset(u8* dest, u8 val, u32 len){
		u8* tmp = (u8*)dest;
		for(;len != 0; len--) *tmp++ = val;
}

//@TODO poprawic tego biedackiego malloca
u32 kmalloc_intrnl(size_t size, short int align, u32 *phys_addr){
		static u32 placement_addr=0x10000;
		if(align != 0 && (placement_addr & 0xFFFFF000)){
				placement_addr &= 0xFFFFF000;
				placement_addr += 0x1000;
		}
		if(phys_addr) *phys_addr = placement_addr;
		u32 ret = placement_addr;
		placement_addr += size;
		return ret;
}

u32 kmalloc(size_t size){
		return kmalloc_intrnl(size, 0, NULL);
}
u32 kmalloc_a(size_t size){
		return kmalloc_intrnl(size, 1, NULL);
}
u32 kmalloc_p(size_t size, u32* phys_addr){
		return kmalloc_intrnl(size, 0, phys_addr);
}
u32 kmalloc_ap(size_t size, u32* phys_addr){
		return kmalloc_intrnl(size, 1, phys_addr);
}
