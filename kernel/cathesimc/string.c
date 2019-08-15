#include "./string.h"
#include "../cpu/types.h"
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
		rstr(str, i-1);
		return str;
}
void concate(char* lth, char* rth){
		int i, j=0;
		for(i=0; lth[i]!='\0'; i++);
		while(rth[j] != '\0'){
				lth[++i]=rth[j++];
		}
}
int strlen(char* str){
		int i=0;
		while(str[i]!='\0') i++;
		return i;
}
void append(char* lth, char rth){
		lth[strlen(lth)+1]=rth;
}
void rstr(char* str, int len){
		int i;
		char tmp;
		for (i=0; i < len/2+1; i++){
				tmp = str[i];
				str[i]=str[len-i];
				str[len-i]=tmp;
		}
}
char* htoa(int n, char* str){
		append(str, '0');
    append(str, 'x');
    char zeros = 0;

    u32 tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp > 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
		return str;

}
