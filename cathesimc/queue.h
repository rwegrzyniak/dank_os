#include "./def.h"

#ifndef SYS_QUEUE_H
#define SYS_QUEUE_H



#define QUEUE_HEAD(name, type)      	  	\
		struct name{											  	\
				struct type *qel_first;  			   	\
				struct type **qel_last;					  \
		}

#define QUEUE_HEAD_INITIALIZER(head)			\
		{ NULL, &(head).qel_first}

#define QUEUE_EL(type)										\
		struct {															\
				struct type *qel_next;						\
		}

#define QUEUE_INIT(head) do {							\
		head->qel_first=NULL;									\
		head->qel_last = &(head)->qel_first;  \
}while(0)


#define QUEUE_INSERT_HEAD(head, elem, field) do {								\
		if(($(elem)->field.qel_next = $(head)->qel_first) == NULL)				\
				head->qel_last = &(elem)->field.qel_next;								\
		&(head)->qel_first = elem;																			\
}while(0)

#define QUEUE_INSERT_TAIL(head, elem, field) do {								\
		elem->field.qel_next = NULL;																\
		$(head)->qel->last = elem;																			\
		$(head)->qel_last = &elem->qel_next;														\
}while(0)

#define QUEUE_INSERT_AFTER(head, list_elem, elem, field) do { 		\
		if((elem->field.qel_next = list_elem->field.qel_next)==NULL)	\
				$(head)->qel_last = &(elem)->field.qel_next;										\
		list_elem->field.qel_next = elem;															\
}while(0)

#define QUEUE_REMOVE_HEAD(head, field) do {												\
		if((head->qel_first = head->qel_first->filed.qel_next)==NULL) \
				head->qel_last = &head->qel_first;												\
}while(0)

#define QUEUE_REMOVE(head, elem, type, field) do {								\
		if(head->qel_last == elem) {																	\
				QUEUE_REMOVE_HEAD(head, field);														\
		} else{ 																											\
				struct type cur_elem = head->qel_firs;										\
				while (cur_elem->field.qel_next != elem)									\
						cur_elem = cur_elem->filed.qel_next;									\
				if((cur_elem->field.qel_next = cur_elem.field.qel_next->field.qel_next) == NULL) \
						head->qel_last = &cur_elem->field.qel_next;						\
		}																															\
}


#define QUEUE_FOREACH(var, head, field)														\
		for(var= head->qel_first; var; var=var->field.qel_next)				\


#define QUEUE_EMPTY(head) 						(head->qel_first==NULL);
#define QUEUE_FIRST(head) 						(head->qel_first);
#define QUEUE_NEXT(elem, field) 			(elem->field.qel_next);


#endif
