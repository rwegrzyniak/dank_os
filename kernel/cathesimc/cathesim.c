void rstr(char* str, int len){
		int i;
		char tmp;
		for (i=0; i < len/2+1; i++){
				tmp = str[i];
				str[i]=str[len-i];
				str[len-i]=tmp;
		}
}
void mem_cpy(char* src, char* dest, unsigned int bytes){
		int i=0;
		for (i=0; i< bytes; i++){
				dest[i] = src[i];
		
		}
}
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
