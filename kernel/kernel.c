#include "./drivers/screen.h"
#include "./cpu/idt.h"
#include "./cpu/isr.h"
#include "./drivers/generic_keyboard.h"
#include "../cathesimc/string.h"
#include "./util/panic.h"
#include "./memory/paging.h"
void main() {
		isr_install();
		__asm__ __volatile__("sti");
		clear_screen();
		//char tmp[128];
		/* init_paging(); */
    //u32* ptr = (u32*)0xA0000000;
		//u32 do_page_fault = *ptr;
		//kprint("\n");
		init_generic_keyboard();
		//int i=0;
		//for (i=0; i<8; i++){
			//	kprint_at("#", 40, i);
		//}
		//kprint_at("###", 37, 2);
		//kprint_at("###", 41, 2);
		//kprint_at(" ", 0, 8);
		//kprint("\nSCZESC BOZE! \n");
		kprint_at("+ ", 1, 1);
		char* x = "jan";
		char* y = "dzban";
		char* z;
		int i ;
		concate(x, y);
		concate(x, y);
}
