#include "./paging.h"
#include "../util/panic.h"
#include "./memory.h"
#include "../drivers/screen.h"

page_dir_t* kernel_dir, cur_dir;

//helper function for convinient printing
void pint(u32 a){
		char * tmp;
		itoa(a, tmp);
		kprint(tmp);
		kprint("\n");
}

void init_paging(){
		kernel_dir = kmalloc(sizeof(page_dir_t));
		memset(kernel_dir, 0, 4096);
		pint(sizeof(page_dir_t));
		pint(&kernel_dir->page_tables[0]);
		pint(kernel_dir);
		int i;
		for(i=0; i<1024; i++){ //setting up page directories for kernel
				// read and write and kernel_mode and not present
				kernel_dir->page_tables[i] = (u32)kmalloc(sizeof(page_table_t)) | 0x2;
		}
		map_page_table(kernel_dir->page_tables[0], 1, 1); //map ram to pages;
		kernel_dir->page_tables[0] |= 0x3; //set as present
		PANIC("BOZE DOPOMOZ");
		enable_paging();
}
void map_page_table(page_table_t* p_table, int kernel, int rw){
		int i;
		page_t tmp_page;
		tmp_page.present = 1; 
		tmp_page.rw = (rw) ? 1 : 0;
		tmp_page.kernel_space = (kernel) ? 1: 0;

		for(i=0; i<1024; i++){
				tmp_page.frame |= kmalloc(PAGE_SIZE);
				p_table->pages[i] = tmp_page; 		
		}
}
void enable_paging(){
		u32 cr0_temp_value;
		__asm__ __volatile__("mov %0, %%cr3":: "r"(&kernel_dir->page_tables));
		__asm__ ("mov %%cr0, %0": "=r"(cr0_temp_value));
		cr0_temp_value |= 0x80000000;
		__asm__ __volatile__("mov %0, %%cr0":: "r"(cr0_temp_value));

}
