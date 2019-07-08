
;przyjmuje wskaznik na poczatek napisu w BX
print:
		pusha

print_loop:
		mov al, [bx]
		cmp al, 0
		je done
		mov ah, 0x0e ;zabezpieczenie przed przerwaniem
		int 0x10
		add bx, 1
		jmp print_loop
done:
		popa
		ret
print_endl:
		pusha
		mov ah, 0x0e ;bez przerwania, jeden blok
		mov al, 0x0a
		int 0x10
		mov al, 0x0d
		int 0x10
		
		popa
		ret

		


