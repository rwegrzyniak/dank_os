#include "./string.h"
#include "../kernel/cpu/types.h"
#include "./stdarg.h"
#include "../kernel/drivers/screen.h"

char* itoa(int n, char* str){
		int i=0;
		unsigned char sign=0x0;
		if (n < 0) {
				n = -n;
				sign = 0x1;
		}
		do{
				str[i++] = n % 10 + '0';
		} while((n/=10)>0);
		if (sign!=0x0) str[i++] = '-';
		str[i] = '\0';
		rstr(str);
		return str;
}
void concate(char* lth, char* rth){
		int i, j=0;
		for(i=0; lth[i]!='\0'; i++);
		while(rth[j] != '\0'){
				lth[++i - 1]=rth[j++];
		}
}
int strlen(char* str){
		int i=0;
		while(str[i]!='\0') i++;
		return i;
}
void append(char* lth, char rth){
		lth[strlen(lth)]=rth;
}
void rstr(char* str){
		char *p1, *p2;
		for(p1 = str, p2 = str + strlen(str) - 1; p1 < p2; ++p1, --p2){
				*p1 ^= *p2;
				*p2 ^= *p1;
				*p1 ^= *p2;
		}
}
char* htoa(int n, char* str){
		str[0] = '0';
		str[1] = 'x';
		int nr_zeroes = 2;
		int zeroes = 1;
		int i;
		for (i = 7; i >= 0; i--){
			str[7-i+nr_zeroes] = (n >> i*4) & 0xf;
			char* ch;

			if (str[7-i+nr_zeroes] == 0 && 7-i+nr_zeroes == 2){
				nr_zeroes--;
				continue;
			}

			zeroes = 0;
			str[7-i+nr_zeroes] += (str[7-i+nr_zeroes] < 10 ? '0' : ('A' - 10));
		}
		return str;
}
void printf(char* str, ...){
		char buffer[256];
		char conversionBuffer[256];
		buffer[0] = '\0';

		char* trav;
		unsigned int i;
		char* x;
		
		va_list arg;
		va_start(arg, str);

		for (trav = str; *trav != '\0'; trav++) {
				if (*trav != '%') {
						append(buffer, *trav);
						continue;
				}

				trav++;

				switch(*trav) {
						case 'd': 
								i = va_arg(arg, int);
								itoa(i, conversionBuffer);
								concate(buffer, conversionBuffer);
								break;
						case 'x': 
								i = va_arg(arg, int);
								htoa(i, conversionBuffer);
								concate(buffer, conversionBuffer);
								break;
						case 's': 
								x = va_arg(arg, char*);
								concate(buffer, x);
								break;
						case 'c': 
								i = va_arg(arg, int);
								append(buffer, i);
								break;
				}
		}

		va_end(arg);
		
		kprint(buffer);
}
