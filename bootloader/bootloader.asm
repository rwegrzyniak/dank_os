[org 0x7c00] ; bootloader offset
KERNEL_OFFSET equ 0x1000
		mov [BOOT_DRIVE], dl

    mov bp, 0x9000 ; set the stack
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print ; This will be written after the BIOS messages
		call print_endl
		call load_kernel
		
		mov bx, MSG_SWITCHING_TO_PROT_MODE
		call print
		call print_endl

    call enable_pm
		call print_endl
		jmp $ ; this will actually never be executed

%include "bootloader/libs/tty_driver.asm"
%include "bootloader/libs/hdd_driver.asm"
%include "bootloader/libs/gdt.asm"
%include "bootloader/libs/print.asm"
%include "bootloader/libs/enable_pm.asm"

[bits 16]
load_kernel:
		mov bx, KERNEL_OFFSET
		mov dh, 32
		mov dl, [BOOT_DRIVE]
		call read_from_disk
		
		mov bx, MSG_KERNEL_LOADING_DONE
		call print
		call print_endl
		ret


[bits 32]
BEGIN_PM: ; after the switch we will get here
    mov ebx, MSG_PROT_MODE
    call print_32_pm ; Note that this will be written at the top left corner
		mov ebx, MSG_STARTING_KERNEL
		call print_32_pm
		call KERNEL_OFFSET
    jmp $

BOOT_DRIVE:
		db 0



MSG_STARTING_KERNEL:
		db "Starting kernel...", 0
MSG_REAL_MODE:
		db "Started 16-bit real mode", 0
MSG_SWITCHING_TO_PROT_MODE:
		db "Swithing to 32-bit protected mode...", 0
MSG_PROT_MODE:
		db "Loaded 32-bit protected mode", 0
MSG_KERNEL_LOADING_DONE:
		db "Kernel loaded", 0


; bootsector
times 510-($-$$) db 0
dw 0xAA55
