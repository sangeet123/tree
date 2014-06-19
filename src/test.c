#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/avl.h"
#include "lib/list.h"

void node_initialize(AVLTreePtr tree, AVLTreeNodePtr *node, char *word);
int comp(void* first, void* second);
char* get_string(void *data);

int main(){
	AVLTreePtr tree = avltree_allocate();
	char *words[] = {
		"something",
		"done",
		"wrong",
		"is",
		"hello",
		"jpt",
		"src",
		"run",
		"media",
		"data",
		"projects",
		"c",
		"playground",
		"data",
		"structures",
		"main"
	};
	// int words[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	int counter = 0;
	while(counter<16){
		AVLTreeNodePtr node = avltree_node_allocate(tree);
		node_initialize(tree, &node, words[counter]);
		avltree_insert(tree, node, comp);
		printf("%d: %s\n", counter, words[counter]);
		counter++;
	}
	bfs_avltree_walk(tree, get_string);
	// AVLTreeNodePtr node = avltree_search(tree, tree->root, words[8], comp);

	// if(node != NULL || node != tree->NIL){
	// 	avltree_delete(tree, node);
	// 	bfs_avltree_walk(tree, get_string);
	// }
	return 0;
}


void node_initialize(AVLTreePtr tree, AVLTreeNodePtr *node, char *word){
	(*node)->right = tree->NIL;
	(*node)->left = tree->NIL;
	(*node)->parent = tree->NIL;
	(*node)->data = word;
}

// int comp(void* first, void* second){
// 	return (*((int*)first) - *((int*)second));
// }
int comp(void* first, void* second){
	return strcmp((char *)first, (char *) second);
}

char* get_string(void *data){
	if (data == NULL)
		return "NULL";
	// int value = *((int*) data);
	// printf("converting %d to string", value);
	char* string_val = (char *) malloc(100);
	sprintf(string_val, "%s", (char *) data);
	return string_val;
}
