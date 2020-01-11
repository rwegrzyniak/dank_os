#include "../cpu/types.h"
#include "../../cathesimc/queue.h"

struct key_event{
		char key;
		char is_special;
		char is_down;
		QUEUE_EL(key_event) entries;
};
void init_generic_keyboard();
extern struct keyboard_event_queue_head keyboard_event_qhead;
extern struct keyboard_event_queue_head* keyboard_event_queue_ptr;
