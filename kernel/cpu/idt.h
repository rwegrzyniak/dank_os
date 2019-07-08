#ifndef IDT_H
#define IDT_H

#include "./types.h"


#define IDT_ENTRIES 256
#define KERNEL_CS 0x08


typedef struct{
		u16 l_offset;
		u16 sel;
		u8 always0;
		 /* First byte
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
		u8 flags;
		u16 h_offset;

} __attribute((packed)) idt_gate_t;

typedef struct {
		u16 limit;
		u32 base;
} __atribute__((packed)) idt_reg_t

idt_gate_t idt[IDT_ENTRIES]
idt_reg_t idt_reg

void set_idt_gate(int nm, u32 handler);
void set_idt();


#endif

