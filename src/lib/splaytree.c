#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "splaytree.h"
/*
 * Function: splaytree_node_allocate
 * Purpose: This function allocates/creates a tree node. It sets its parent, left and right child to sentinel tree->NIL.
 * Input Parameters:
 *	SplayTreePtr tree - A tree pointer. Its sole purpose is to be able to use tree->NIL. tree->NIL is a separate tree node pointer for each tree.
 * Output:
 *	RBTreeNodePTr - Newly allocated memory for the tree node.
 */
SplayTreeNodePtr splaytree_node_allocate(SplayTreePtr tree){
	SplayTreeNodePtr splaytree_node_ptr = (SplayTreeNodePtr) malloc(sizeof(Treenode));
	splaytree_node_ptr->left = tree->NIL;
	splaytree_node_ptr->right = tree->NIL;
	splaytree_node_ptr->parent = tree->NIL;
	return splaytree_node_ptr;
}

/*
 * Function: splaytree_allocate
 * Purpose: This function allocates/creates a tree. It sets its NIL tree node such that it stores "NULL" as its data.
 * Input: void
 * Output: SplayTreePtr - Newly allocated memory for the tree.
 */
SplayTreePtr splaytree_allocate(void){
	SplayTreePtr splaytree_ptr = (SplayTreePtr) malloc(sizeof(Tree));
	splaytree_ptr->NIL = splaytree_node_allocate(splaytree_ptr);
	(splaytree_ptr->NIL)->data = NULL;
	splaytree_ptr->root = splaytree_ptr->NIL;
	return splaytree_ptr;
}

/*
 * Function: inorder_splaytree_walk
 * Purpose: This function makes an inorder tree walk
 * Input:
 *	SplayTreePtr tree - Pointer to a tree. It is required for the sentinel tree->NIL
 *	SplayTreeNodePtr root - Pointer to a tree node. This is the root element from where we start the inorder tree walk
 * Output: Prints all the node in inorder order.
 */
void inorder_splaytree_walk(SplayTreePtr tree, SplayTreeNodePtr root, char* (*get_string)(void *)){
	if (root != tree->NIL){
		inorder_splaytree_walk(tree, root->left, get_string);
		printf("%s\n", (*get_string)(root->data));
		inorder_splaytree_walk(tree, root->right, get_string);
	}
}

/*
 * Function: preorder_splaytree_walk
 * Purpose: This function makes a preorder tree walk
 * Input:
 *	SplayTreePtr tree - Pointer to a tree. It is required for the sentinel tree->NIL
 *	SplayTreeNodePtr root - Pointer to a tree node. This is the root element from where we start the preorder tree walk
 * Output: Prints all the node in preorder order.
 */
void preorder_splaytree_walk(SplayTreePtr tree, SplayTreeNodePtr root, char* (*get_string)(void *)){
	if (root != tree->NIL){
		printf("%s\n", (*get_string)(root->data));
		preorder_splaytree_walk(tree, root->left, get_string);
		preorder_splaytree_walk(tree, root->right, get_string);
	}
}

/*
 * Function: postorder_splaytree_walk
 * Purpose: This function makes a postorder tree walk
 * Input:
 *	SplayTreePtr tree - Pointer to a tree. It is required for the sentinel tree->NIL
 *	SplayTreeNodePtr root - Pointer to a tree node. This is the root element from where we start the preorder tree walk
 * Output: Prints all the node in postorder order.
 */
void postorder_splaytree_walk(SplayTreePtr tree, SplayTreeNodePtr root, char* (*get_string)(void *)){
	if (root != tree->NIL){
		postorder_splaytree_walk(tree, root->left, get_string);
		postorder_splaytree_walk(tree, root->right, get_string);
		printf("%s\n", (*get_string)(root->data));
	}
}

/*
 * Function: bfs_splaytree_walk
 * Purpose: This function makes a level order(breadth-first) tree walk
 * Input:
 *	SplayTreePtr tree - Pointer to a tree. It is required for the sentinel tree->NIL
 *  char* (*get_string)(void*) - Function pointer to a function which takes a void pointer as input parameter. The function should return char pointer for that void*.
 * Output: Prints all the node in preorder order.
 */
void bfs_splaytree_walk(SplayTreePtr tree, char* (*get_string)(void*)){
	// Create a list to store nodes
	LIST list = list_allocate();
	// Create a new linked list node and assign the root of the tree
	NODE node = node_allocate();
	SplayTreeNodePtr root = tree->root;
	node->data = root;
	// Enqueue this node in the list
	list_enqueue(list, node);

	// Repeat this loop while there is any node in enqueue
	// Dequeue node from the list. Print its related data and add its children to the queue
	while (has_next(list)){
		NODE current = list_dequeue(list);
		printf("%s\t left: %s\t right: %s\t parent:%s\n", \
			(*get_string)(((SplayTreeNodePtr)(current->data))->data), \
			(*get_string)((((SplayTreeNodePtr)(current->data))->left)->data), \
			(*get_string)((((SplayTreeNodePtr)(current->data))->right)->data), \
			(*get_string)((((SplayTreeNodePtr)(current->data))->parent)->data) \
			);
		
		if (((SplayTreeNodePtr)(current->data))->left != tree->NIL){
			NODE left_child = node_allocate();
			left_child->data = ((SplayTreeNodePtr)(current->data))->left;
			list_enqueue(list, left_child);
		}

		if (((SplayTreeNodePtr)(current->data))->right != tree->NIL){
			NODE right_child = node_allocate();
			right_child->data = ((SplayTreeNodePtr)(current->data))->right;
			list_enqueue(list, right_child);
		}

	}
}

/*
 * Function: splaytree_search
 * Purpose: This function searches whether a data is in the RB Tree or not and returns the node if found otherwise returns tree->NIL
 * Input:
 *	SplayTreePtr tree: The tree to search on
 *	SplayTreeNodePtr root: The root of the tree to begin the search
 *	void *data: A void pointer to the data.
 *	int (*comp)(void*, void*): Pointer to a function which takes two void* parameters, compares them and returns -1, 0 and 1 similar to what strcmp does
 */
SplayTreeNodePtr splaytree_search(SplayTreePtr tree, SplayTreeNodePtr root, void *data, int (*comp)(void*, void*)){
	int compare_value =  (*comp)(data, root->data);
	if (compare_value == 0){
		splay(tree, root);
		return root;
	}
	if (compare_value < 0){
		if (root->left == tree->NIL){
			splay(tree, root);
			return tree->NIL;
		}
		else
			return splaytree_search(tree, root->left, data, comp);
	}
	else{
		if (root->right == tree->NIL){
			splay(tree, root);
			return tree->NIL;
		}
		else
			return splaytree_search(tree, root->right, data, comp);
	}
}

/*
 * Function: splaytree_min
 * Purpose: This function returns the node having the minimum value in the subtree rooted at "root"
 * Input:
 *	SplayTreePtr tree: The tree to search on
 *	SplayTreeNodePtr root: The root of the tree to begin the search
 */
SplayTreeNodePtr splaytree_min(SplayTreePtr tree, SplayTreeNodePtr root){
	while(root->left != tree->NIL)
		root = root->left;
	splay(tree, root);
	return root;
}

/*
 * Function: splaytree_max
 * Purpose: This function returns the node having the maximum value in the subtree rooted at "root"
 * Input:
 *	SplayTreePtr tree: The tree to search on
 *	SplayTreeNodePtr root: The root of the tree to begin the search
 */
SplayTreeNodePtr splaytree_max(SplayTreePtr tree, SplayTreeNodePtr root){
	while(root->right != tree->NIL)
		root = root->right;
	splay(tree, root);
	return root;
}

SplayTreeNodePtr splaytree_successor(SplayTreePtr tree, SplayTreeNodePtr node){
	if(node->right != tree->NIL)
		return splaytree_min(tree, node->right);
	SplayTreeNodePtr parent = node->parent;
	while(parent != tree->NIL && node == parent->right){
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

SplayTreeNodePtr splaytree_predecessor(SplayTreePtr tree, SplayTreeNodePtr node){
	if(node->left != tree->NIL)
		return splaytree_max(tree, node->left);
	SplayTreeNodePtr parent = node->parent;
	while(parent != tree->NIL && node == parent->left){
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

void splaytree_insert(SplayTreePtr tree, SplayTreeNodePtr node, int (*comp)(void*, void*)){
	SplayTreeNodePtr parent = tree->NIL;
	SplayTreeNodePtr current = tree->root;
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
	splay(tree, node);
}

void transplant(SplayTreePtr tree, SplayTreeNodePtr current, SplayTreeNodePtr next){
	if (current->parent == tree->NIL)
		tree->root = next;
	else if ((current->parent)->left == current)
		(current->parent)->left = next;
	else if ((current->parent)->right == current)
		(current->parent)->right = next;
	next->parent = current->parent;
}

void splaytree_delete(SplayTreePtr tree, SplayTreeNodePtr node){
	
	if (node->left == tree->NIL)
		transplant(tree, node, node->right);
	else if (node->right == tree->NIL)
		transplant(tree, node, node->left);
	else {
		SplayTreeNodePtr successor = splaytree_min(tree, node->right);
		if (successor != node->right){
			transplant(tree, successor, successor->right);
			successor->right = node->right;
			(successor->right)->parent = successor;
		}
		transplant(tree, node, successor);
		successor->left = node->left;
		(successor->left)->parent = successor;
	}
}


void left_rotate(SplayTreePtr tree, SplayTreeNodePtr node){
	/* Left rotate uses right edge of node*/
	SplayTreeNodePtr right_child = node->right;
	if (right_child == tree->NIL)
		return;
	else{
		/* Make left child of right_child, right child of node */
		node->right = right_child->left;
		if (node->right != tree->NIL)
			(node->right)->parent = node;

		/* Make the right_child child of node's parent*/
		right_child->parent = node->parent;
		// If this node's parent is NIL, this node must be root. Root information must be maintained in the "tree".
		if (node->parent == tree->NIL)
			tree->root = right_child;
		if ((node->parent)->left == node)
			(node->parent)->left = right_child;
		else
			(node->parent)->right = right_child;

		/* Make node left child of right_child*/
		right_child->left = node;
		node->parent = right_child;
	}
}

void right_rotate(SplayTreePtr tree, SplayTreeNodePtr node){
	/* Right rotate uses left edge of node */
	SplayTreeNodePtr left_child = node->left;
	if (left_child == tree->NIL)
		return;
	else {
		/* Make right child of left_child, left child of node*/
		node->left = left_child->right;
		if (node->left != tree->NIL)
			(node->left)->parent = node;
		
		/* Make the left_child child of node's parent */
		left_child->parent = node->parent;
		// If this node's parent is NIL, this node must be root. Root information must be maintained in the "tree".
		if (node->parent == tree->NIL)
			tree->root = left_child;
		if((node->parent)->left == node)
			(node->parent)->left = left_child;
		else
			(node->parent)->right = left_child;

		/* Make node right child of left_child */
		left_child->right = node;
		node->parent = left_child;
	}
}

void splay(SplayTreePtr tree, SplayTreeNodePtr node){
	while(node != tree->root){
		if (node == (node->parent)->left){
			// Current node is left child of its parent
			// Case 1. Zig
			// Current node is left child of the root
			if (node->parent == tree->root){
				right_rotate(tree, tree->root);
			}
			// Case 2. Zig Zag
			// Current node's parent is right child of its grandparent
			else if (node->parent == ((node->parent)->parent)->right){
				right_rotate(tree, node->parent);
				left_rotate(tree, node->parent);
			}
			// Case 3. Zig Zig
			// Current node's parent is left child of its grandparent
			else if (node->parent == ((node->parent)->parent)->left){
				right_rotate(tree, (node->parent)->parent);
				right_rotate(tree, node->parent);
			}
		}
		else {
			// Current node is right child of its parent
			// Case 1. Zig
			// Current node is right child of the root
			if (node->parent == tree->root){
				left_rotate(tree, tree->root);
			}
			// Case 2. Zig Zag
			// Current node's parent is left child of its grandparent
			else if (node->parent == ((node->parent)->parent)->left){
				left_rotate(tree, node->parent);
				right_rotate(tree, node->parent);
			}
			// Case 3. Zig Zig
			// Current node's parent is right child of its grandparent
			else if (node->parent == ((node->parent)->parent)->right){
				left_rotate(tree, (node->parent)->parent);
				left_rotate(tree, node->parent);
			}
		}
	}
}

