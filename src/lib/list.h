/*
 * list.h
 * Author: Sangeet Dahal
 */

#ifndef LIST_H_
#define LIST_H_

typedef struct list_node* NODE;
typedef struct list_node {
	void *data;
	NODE next;
	NODE prev;
} NODE_STRUCT;

typedef struct list* LIST;
typedef struct list
{
	NODE NIL;
}LIST_STRUCT;

NODE node_allocate();
LIST list_allocate(void);
NODE list_search(LIST list, void* data);
void list_push(LIST list, NODE node);
void list_enqueue(LIST list, NODE node);
NODE list_pop(LIST list);
NODE list_dequeue(LIST list);
int has_next(LIST list);


#endif	/* LIST_H_ */