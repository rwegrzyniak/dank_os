#include "../cpu/types.h"
#include "../cathesimc/queue.h"


struct key_event{
		char key;
		char is_special;
		char is_down;
		QUEUE_EL(key_event) entries;
};
QUEUE_HEAD(keyboard_event_queue_head, key_event) keyboard_event_qhead = QUEUE_HEAD_INITIALIZER(keyboard_event_qhead);
void init_generic_keyboard();
