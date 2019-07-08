;czyta dh sektorow z dysku dl i zapisuje do es:bx
read_from_disk:
		pusha
		push dx
		
		mov ah, 0x02 ;reading mode
		mov al, dh
		mov cl, 0x02 ;offset do liczenia sectorow (pierwszy to boot sector
		mov ch, 0x00 ; cylinder
		mov dh, 0x00 ;glowica


		int 0x13
		jc disk_err

		pop dx
		cmp al, dh ;czy odczytane tyle secterow ile trzeva
		jne sectors_err
		popa
		ret
disk_err:
		mov bx, DISK_ERR_MSG
		call print
		call print_endl
		mov bx, dx
		call print
		pop dx

		jmp disk_err_loop
disk_err_loop:
		jmp $
sectors_err:
		mov bx, SECTORS_ERR_MSG
		call print
		jmp disk_err_loop
DISK_ERR_MSG:
		db "Blad odczytu z dysku ty jebana polska kurwo ", 0
SECTORS_ERR_MSG:
		db "Odczytano za malo sektorow ty jebana polska kurwo", 0


