#include <stdlib.h>
#include <stdio.h>
#include "avl.h"
#include "list.h"

AVLTreeNodePtr avltree_node_allocate(AVLTreePtr tree){
	AVLTreeNodePtr node = (AVLTreeNodePtr) malloc(sizeof(Treenode));
	node->left = tree->NIL;
	node->right = tree->NIL;
	node->parent = tree->NIL;
	node->height = 0;
	return node;
}


AVLTreePtr avltree_allocate(void){
	AVLTreePtr tree = (AVLTreePtr) malloc(sizeof(Tree));
	tree->NIL = avltree_node_allocate(tree);
	(tree->NIL)->data = NULL;
	(tree->NIL)->height = -1;
	tree->root = tree->NIL;
	
	return tree;
}

int get_height(AVLTreePtr tree, AVLTreeNodePtr node){
	if (node == tree->NIL)
		return -1;
	else
		return max(get_height(tree,node->left), get_height(tree, node->right));
}

void inorder_avl_tree_walk(AVLTreePtr tree, AVLTreeNodePtr root, char* (*get_string)(void *)){
	if (root != tree->NIL){
		inorder_avl_tree_walk(tree, root->left, get_string);
		printf("%d: %s\n", root->height, (*get_string)(root->data));
		inorder_avl_tree_walk(tree, root->right, get_string);
	}
}

void preorder_avl_tree_walk(AVLTreePtr tree, AVLTreeNodePtr root, char* (*get_string)(void *)){
	if (root != tree->NIL){
		printf("%s\n", (*get_string)(root->data));
		preorder_avl_tree_walk(tree, root->left, get_string);
		preorder_avl_tree_walk(tree, root->right, get_string);
	}
}

void postorder_avl_tree_walk(AVLTreePtr tree, AVLTreeNodePtr root, char* (*get_string)(void *)){
	if (root != tree->NIL){
		postorder_avl_tree_walk(tree, root->left, get_string);
		postorder_avl_tree_walk(tree, root->right, get_string);
		printf("%s\n", (*get_string)(root->data));
	}
}

/*
 * Function: bfs_rbtree_walk
 * Purpose: This function makes a level order(breadth-first) tree walk
 * Input:
 *	AVLTreePtr tree - Pointer to a tree. It is required for the sentinel tree->NIL
 *  char* (*get_string)(void*) - Function pointer to a function which takes a void pointer as input parameter. The function should return char pointer for that void*.
 * Output: Prints all the node in preorder order.
 */
void bfs_avltree_walk(AVLTreePtr tree, char* (*get_string)(void*)){
	// Create a list to store nodes
	LIST list = list_allocate();
	// Create a new linked list node and assign the root of the tree
	NODE node = node_allocate();
	AVLTreeNodePtr root = tree->root;
	node->data = root;
	// Enqueue this node in the list
	list_enqueue(list, node);

	// Repeat this loop while there is any node in enqueue
	// Dequeue node from the list. Print its related data and add its children to the queue
	while (has_next(list)){
		NODE current = list_dequeue(list);
		printf("%s\t height: %d\t left: %s\t right: %s\t parent:%s\n", \
			(*get_string)(((AVLTreeNodePtr)(current->data))->data), \
			((AVLTreeNodePtr)(current->data))->height, \
			(*get_string)((((AVLTreeNodePtr)(current->data))->left)->data), \
			(*get_string)((((AVLTreeNodePtr)(current->data))->right)->data), \
			(*get_string)((((AVLTreeNodePtr)(current->data))->parent)->data) \
			);
		
		if (((AVLTreeNodePtr)(current->data))->left != tree->NIL){
			NODE left_child = node_allocate();
			left_child->data = ((AVLTreeNodePtr)(current->data))->left;
			list_enqueue(list, left_child);
		}

		if (((AVLTreeNodePtr)(current->data))->right != tree->NIL){
			NODE right_child = node_allocate();
			right_child->data = ((AVLTreeNodePtr)(current->data))->right;
			list_enqueue(list, right_child);
		}

	}
}
AVLTreeNodePtr avltree_search(AVLTreePtr tree, AVLTreeNodePtr root, char *data, int (*comp)(void *, void *)){
	if (root == tree->NIL || (*comp)(data, root->data) == 0)
		return root;
	if ((*comp)(data, root->data) < 0)
		return avltree_search(tree, root->left, data, comp);
	else
		return avltree_search(tree, root->right, data, comp);
}

AVLTreeNodePtr avltree_min(AVLTreePtr tree, AVLTreeNodePtr root){
	while(root->left != tree->NIL)
		root = root->left;
	return root;
}

AVLTreeNodePtr avltree_max(AVLTreePtr tree, AVLTreeNodePtr root){
	while(root->right != tree->NIL)
		root = root->right;
	return root;
}

AVLTreeNodePtr tree_successor(AVLTreePtr tree, AVLTreeNodePtr node){
	if(node->right != tree->NIL)
		return avltree_min(tree, node->right);
	AVLTreeNodePtr parent = node->parent;
	while(parent != tree->NIL && node == parent->right){
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

AVLTreeNodePtr tree_predecessor(AVLTreePtr tree, AVLTreeNodePtr node){
	if(node->left != tree->NIL)
		return avltree_max(tree, node->left);
	AVLTreeNodePtr parent = node->parent;
	while(parent != tree->NIL && node == parent->left){
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

void avltree_insert(AVLTreePtr tree, AVLTreeNodePtr node, int (*comp)(void *, void *)){
	
	AVLTreeNodePtr parent = tree->NIL;
	AVLTreeNodePtr current = tree->root;
	while(current != tree->NIL){
		parent = current;
		if ((*comp)(node->data, current->data) <= 0)
			current = current->left;
		else
			current = current->right;
	}
	node->parent = parent;
	if (parent == tree->NIL){
		tree->root = node;
	}
	else if ((*comp)(node->data, parent->data) <= 0){
		parent->left = node;
	}
	else{
		parent->right = node;
	}

	avlcalculate_height(tree, node);
}

void avlcalculate_height(AVLTreePtr tree, AVLTreeNodePtr node){
	while (node != tree->NIL){
		node->height = max((node->left)->height, (node->right)->height) + 1;
		node = node->parent;
	}
}

void avl_transplant(AVLTreePtr tree, AVLTreeNodePtr current, AVLTreeNodePtr next){
	if (current->parent == tree->NIL)
		tree->root = next;
	else if ((current->parent)->left == current)
		(current->parent)->left = next;
	else if ((current->parent)->right == current)
		(current->parent)->right = next;
	next->parent = current->parent;
}

void avltree_delete(AVLTreePtr tree, AVLTreeNodePtr node){
	if (node->left == tree->NIL)
		avl_transplant(tree, node, node->right);
	else if (node->right == tree->NIL)
		avl_transplant(tree, node, node->left);
	else {
		AVLTreeNodePtr successor = avltree_min(tree, node->right);
		if (successor != node->right){
			avl_transplant(tree, successor, successor->right);
			successor->right = node->right;
			(successor->right)->parent = successor;
		}
		avl_transplant(tree, node, successor);
		successor->left = node->left;
		(successor->left)->parent = successor;
	}
}

inline int max(int first, int second){
	return (first>second?first:second);
}
