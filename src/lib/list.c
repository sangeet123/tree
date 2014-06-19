#include <stdio.h>
#include <stdlib.h>
#include "list.h"

NODE node_allocate(){
	return (NODE) malloc(sizeof(NODE_STRUCT));
}

LIST list_allocate(void){
	LIST list = (LIST) malloc(sizeof(LIST_STRUCT));
	list->NIL = (NODE) malloc(sizeof(NODE_STRUCT));
	(list->NIL)->prev = list->NIL;
	(list->NIL)->next = list->NIL;
	(list->NIL)->data = NULL;
	return list;
}

NODE list_search(LIST list, void* data){
	NODE pointer = (list->NIL)->next;
	while (pointer != list->NIL && pointer->data != data)
		pointer = pointer->next;
	return pointer;
}

void list_push(LIST list, NODE node){
	node->next = (list->NIL)->next;
	(node->next)->prev = node;
	(list->NIL)->next = node;
	node->prev = list->NIL;
}

void list_enqueue(LIST list, NODE node){
	node->prev = (list->NIL)->prev;
	(node->prev)->next = node;
	(list->NIL)->prev = node;
	node->next = list->NIL;
}

NODE list_pop(LIST list){
	NODE pointer = (list->NIL)->next;
	// printf("Node to pop out: %p\n", pointer->data);
	(pointer->next)->prev = list->NIL;
	(list->NIL)->next = pointer->next;

	return pointer;
}

NODE list_dequeue(LIST list){
	return list_pop(list);
}

int has_next(LIST list){
	if ((list->NIL)->next == list->NIL)
		return 0;
	else return 1;
}