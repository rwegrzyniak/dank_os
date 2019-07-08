#include "./drivers/screen.h"

void main() {
    clear_screen();
		int i=0;
		for (i=0; i<8; i++){
				kprint_at("#", 40, i);
		}
		kprint_at("###", 37, 2);
		kprint_at("###", 41, 2);
		kprint_at(" ", 0, 8);
		kprint("\nSCZESC BOZE! \n");
		kprint("+");
		/*
		for (i = 0; i < 24; i++) {
        char str[255];
        itoa(i, str);
        kprint_at(str, 0, i);
    }

    kprint_at("This text forces the kernel to scroll. Row 0 will disappear. ", 60, 24);
		kprint("And with this text, the kernel will scroll again, and row 1 will disappear too!");*/
}
