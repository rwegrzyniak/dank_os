#include "./drivers/screen.h"
#include "./cpu/idt.h"
#include "./cpu/isr.h"
#include "./drivers/generic_keyboard.h"
#include "../cathesimc/string.h"

void main() {
		isr_install();
		asm volatile("sti");
    clear_screen();
		init_generic_keyboard();
		int i=0;
		for (i=0; i<8; i++){
				kprint_at("#", 40, i);
		}
		kprint_at("###", 37, 2);
		kprint_at("###", 41, 2);
		kprint_at(" ", 0, 8);
		kprint("\nSCZESC BOZE! \n");
		kprint("+ ");

		u32 phys_addr;
		u32 page = kmalloc(1000, 1, &phys_addr);
		char page_str[16] = "";
		itoa(page, page_str);
		char phys_str[16] = "";
		htoa(phys_addr, phys_str);
		kprint("Page: ");
		kprint(page_str);
		kprint(", physical address: ");
		kprint(phys_str);
		kprint("\n");
}
