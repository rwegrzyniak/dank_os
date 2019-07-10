#include "./drivers/screen.h"
#include "./cathesim.h"
#include "./cpu/idt.h"
#include "./cpu/isr.h"
#include "./drivers/generic_keyboard.h"


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
}
