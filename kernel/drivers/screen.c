#include "./ports.h"
#include "./screen.h"
#include "../../cathesimc/memory.h"

int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);
int handle_scroll(int offset);

void kprint_at(char *str, int col, int row){
		int offset;
		if (col>=0 && row>=0) get_offset(col, row);
		else{
				offset = get_cursor_offset();
				row = get_offset_row(offset);
				col = get_offset_col(offset);
		}
		int i=0;
		while(str[i] != 0){
				offset = print_char(str[i++], col, row, SUPREMACY_TTY_COLOR);
				row = get_offset_row(offset);
				col = get_offset_col(offset);
		}
}
void kprint(char *str){
		kprint_at(str, -1, -1);
}
keprint(char* err){
		int i=0;
		int offset = get_cursor_offset();
		int row = get_offset_row(offset);
		int col = get_offset_col(offset);

		while(err[i] != 0){
				offset = print_char(err[i++], col, row, SUPREMACY_TTY_COLOR);
				row = get_offset_row(offset);
				col = get_offset_col(offset);
		}		

}



int print_char(char c, int col, int row, char attr){
		unsigned char* vga_mem=  (unsigned char*) VGA_ADDRESS;
		if (!attr) attr = SUPREMACY_TTY_COLOR;
		if (col>= MAX_COLS || row >= MAX_ROWS){
				//keprint("owiedzmy to wyraznie: te wszystkie (tfu!) sterowniki od VGA calkowicie\
					//	bezczelnie odmawiaja printowania narzucajac eurokolchozowe normy MAX_ROW\
						//ri MAX col, podobnie zreszta jak za czasow Htilera");
				vga_mem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vga_mem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
				return get_offset(col, row);

		}
		int offset;
		if (col>=0 && row>=0) offset = get_offset(col, row);
		else offset=get_cursor_offset();

		if (c == '\n') {
				row= get_offset_row(offset);
				offset = get_offset(0, row+1);
		}
		else {
				vga_mem[offset]= c;
				vga_mem[offset+1] = attr;
				offset+=2;
		}
		offset = handle_scroll(offset);
		set_cursor_offset(offset);
		return offset;
}
int  handle_scroll(int  offset) {
		if (offset  < MAX_ROWS*MAX_COLS *2) {return  offset;}
		int i;for (i=1; i<MAX_ROWS; i++) {
				mem_cpy(get_offset(0,i) + VGA_ADDRESS ,
								get_offset (0,i-1) + VGA_ADDRESS ,
								MAX_COLS *2);
		}
		char* last_line = get_offset(0,MAX_ROWS -1) + VGA_ADDRESS;
		for (i=0; i < MAX_COLS *2; i++) {
				last_line[i] = 0;}
		offset  -= 2* MAX_COLS;
		return  offset;
}
int get_cursor_offset() {
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; // pobnrany zostal wysoki bajt stad << 8
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; 
}

void set_cursor_offset(int offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char* vga_mem = VGA_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        vga_mem[i*2] = ' ';
        vga_mem[i*2+1] = SUPREMACY_TTY_COLOR;
    }
    set_cursor_offset(get_offset(0, 0));
}

int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }
