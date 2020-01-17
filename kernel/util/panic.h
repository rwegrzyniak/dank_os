#define PANIC(msg) do {					\
		kprint('KERNEL_PANIC\n');		\
		kprint(msg);								\
		for(;;);										\
}while(0)
