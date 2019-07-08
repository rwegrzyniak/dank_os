void rstr(char* str, int len){
		int i;
		char tmp;
		for (i=0; i < len+1; i++){
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
void itoa(int n, char* str){
		int i=0, with_sign;
		if ((with_sign=n) < 0) n = -n;
		do{
				str[i++] = n % 10 + '0';
		} while((n/=10)>0);
		if (with_sign != n) str[i++] = '-';
		str[i] = '\0';
		rstr(str, i-1);
}
