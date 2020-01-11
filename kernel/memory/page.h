#ifndef PAGE_H
#define PAGE_H

#include "../cpu/types.h"
#include "../cpu/isr.h"

typedef struct page{
		u32 present			:1;
		u32 rw					:1;
		u32 user_space	:1;
		u32 accessed		:1;
		u32 dirty				:1;
		u32 unused			:7;
		u32 frame				:20;
} page_t;

typedef page_table{
		page_t pages[1024];
} page_table_t;

typedef struct page_directory{
		page_table_t* table[1024];

		u32 tables_physical_addresses[1024];

		u32 phys_address;
} page_dir_t;

void init_paging();


void switch_page_dir(page_dir_t* new_dir);

page_t* get_page(u32 addres, page_dir_t* dir, short int make);

void page_fault(registers_t regs);
