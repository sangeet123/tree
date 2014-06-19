#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "rbtree.h"
/*
 * Function: rbtree_node_allocate
 * Purpose: This function allocates/creates a tree node. It sets its parent, left and right child to sentinel tree->NIL.
 * Input Parameters:
 *	RBTreePtr tree - A tree pointer. Its sole purpose is to be able to use tree->NIL. tree->NIL is a separate tree node pointer for each tree.
 * Output:
 *	RBTreeNodePTr - Newly allocated memory for the tree node.
 */
RBTreeNodePtr rbtree_node_allocate(RBTreePtr tree){
	RBTreeNodePtr rbtree_node_ptr = (RBTreeNodePtr) malloc(sizeof(Treenode));
	rbtree_node_ptr->left = tree->NIL;
	rbtree_node_ptr->right = tree->NIL;
	rbtree_node_ptr->parent = tree->NIL;
	return rbtree_node_ptr;
}

/*
 * Function: rbtree_allocate
 * Purpose: This function allocates/creates a tree. It sets its NIL tree node such that it stores "NIL" as its character data and color as RBBLACK.
 * Input: void
 * Output: RBTreePtr - Newly allocated memory for the tree.
 */
RBTreePtr rbtree_allocate(void){
	RBTreePtr rbtree_ptr = (RBTreePtr) malloc(sizeof(Tree));
	rbtree_ptr->NIL = rbtree_node_allocate(rbtree_ptr);
	(rbtree_ptr->NIL)->data = NULL;
	(rbtree_ptr->NIL)->color = RBBLACK;
	rbtree_ptr->root = rbtree_ptr->NIL;
	return rbtree_ptr;
}

/*
 * Function: inorder_rbtree_walk_depth
 * Purpose: This function makes an inorder tree walk while also printing the depth of the current node
 * Input:
 *	RBTreePtr tree - Pointer to a tree. It is required for the sentinel tree->NIL
 *	RBTreeNodePtr root - Pointer to a tree node. This is the root element from where we start the inorder tree walk
 *	int depth - Integer value indicating the depth of previous level.
 * Output: Prints all the node along with their corresponding depth in inorder order.
 */
void inorder_rbtree_walk_depth(RBTreePtr tree, RBTreeNodePtr root, int depth, char* (*get_string)(void *)){
	if (root != tree->NIL){
			inorder_rbtree_walk_depth(tree, root->left, depth + 1, get_string);
			printf("%d: %s\n", depth, (*get_string)(root->data));
			inorder_rbtree_walk_depth(tree, root->right, depth + 1, get_string);
		}
}

/*
 * Function: inorder_rbtree_walk
 * Purpose: This function makes an inorder tree walk
 * Input:
 *	RBTreePtr tree - Pointer to a tree. It is required for the sentinel tree->NIL
 *	RBTreeNodePtr root - Pointer to a tree node. This is the root element from where we start the inorder tree walk
 * Output: Prints all the node in inorder order.
 */
void inorder_rbtree_walk(RBTreePtr tree, RBTreeNodePtr root, char* (*get_string)(void *)){
	if (root != tree->NIL){
		inorder_rbtree_walk(tree, root->left, get_string);
		printf("%s\n", (*get_string)(root->data));
		inorder_rbtree_walk(tree, root->right, get_string);
	}
}

/*
 * Function: preorder_rbtree_walk
 * Purpose: This function makes a preorder tree walk
 * Input:
 *	RBTreePtr tree - Pointer to a tree. It is required for the sentinel tree->NIL
 *	RBTreeNodePtr root - Pointer to a tree node. This is the root element from where we start the preorder tree walk
 * Output: Prints all the node in preorder order.
 */
void preorder_rbtree_walk(RBTreePtr tree, RBTreeNodePtr root, char* (*get_string)(void *)){
	if (root != tree->NIL){
		printf("%s\n", (*get_string)(root->data));
		preorder_rbtree_walk(tree, root->left, get_string);
		preorder_rbtree_walk(tree, root->right, get_string);
	}
}

/*
 * Function: postorder_rbtree_walk
 * Purpose: This function makes a postorder tree walk
 * Input:
 *	RBTreePtr tree - Pointer to a tree. It is required for the sentinel tree->NIL
 *	RBTreeNodePtr root - Pointer to a tree node. This is the root element from where we start the preorder tree walk
 * Output: Prints all the node in postorder order.
 */
void postorder_rbtree_walk(RBTreePtr tree, RBTreeNodePtr root, char* (*get_string)(void *)){
	if (root != tree->NIL){
		postorder_rbtree_walk(tree, root->left, get_string);
		postorder_rbtree_walk(tree, root->right, get_string);
		printf("%s\n", (*get_string)(root->data));
	}
}

/*
 * Function: bfs_rbtree_walk
 * Purpose: This function makes a level order(breadth-first) tree walk
 * Input:
 *	RBTreePtr tree - Pointer to a tree. It is required for the sentinel tree->NIL
 *  char* (*get_string)(void*) - Function pointer to a function which takes a void pointer as input parameter. The function should return char pointer for that void*.
 * Output: Prints all the node in preorder order.
 */
void bfs_rbtree_walk(RBTreePtr tree, char* (*get_string)(void*)){
	// Create a list to store nodes
	LIST list = list_allocate();
	// Create a new linked list node and assign the root of the tree
	NODE node = node_allocate();
	RBTreeNodePtr root = tree->root;
	node->data = root;
	// Enqueue this node in the list
	list_enqueue(list, node);

	// Repeat this loop while there is any node in enqueue
	// Dequeue node from the list. Print its related data and add its children to the queue
	while (has_next(list)){
		NODE current = list_dequeue(list);
		printf("%s\t color: %s\t left: %s\t right: %s\t parent:%s\n", \
			(*get_string)(((RBTreeNodePtr)(current->data))->data), \
			((RBTreeNodePtr)(current->data))->color > 0 ? "RED":"BLACK", \
			(*get_string)((((RBTreeNodePtr)(current->data))->left)->data), \
			(*get_string)((((RBTreeNodePtr)(current->data))->right)->data), \
			(*get_string)((((RBTreeNodePtr)(current->data))->parent)->data) \
			);
		
		if (((RBTreeNodePtr)(current->data))->left != tree->NIL){
			NODE left_child = node_allocate();
			left_child->data = ((RBTreeNodePtr)(current->data))->left;
			list_enqueue(list, left_child);
		}

		if (((RBTreeNodePtr)(current->data))->right != tree->NIL){
			NODE right_child = node_allocate();
			right_child->data = ((RBTreeNodePtr)(current->data))->right;
			list_enqueue(list, right_child);
		}

	}
}

/*
 * Function: rbtree_search
 * Purpose: This function searches whether a data is in the RB Tree or not and returns the node if found otherwise returns tree->NIL
 * Input:
 *	RBTreePtr tree: The tree to search on
 *	RBTreeNodePtr root: The root of the tree to begin the search
 *	void *data: A void pointer to the data.
 *	int (*comp)(void*, void*): Pointer to a function which takes two void* parameters, compares them and returns -1, 0 and 1 similar to what strcmp does
 */
RBTreeNodePtr rbtree_search(RBTreePtr tree, RBTreeNodePtr root, void *data, int (*comp)(void*, void*)){
	int compare_value =  (*comp)(data, root->data);
	if (root == tree->NIL || compare_value == 0)
		return root;
	if (compare_value < 0)
		return rbtree_search(tree, root->left, data, comp);
	else
		return rbtree_search(tree, root->right, data, comp);
}

/*
 * Function: rbtree_min
 * Purpose: This function returns the node having the minimum value in the subtree rooted at "root"
 * Input:
 *	RBTreePtr tree: The tree to search on
 *	RBTreeNodePtr root: The root of the tree to begin the search
 */
RBTreeNodePtr rbtree_min(RBTreePtr tree, RBTreeNodePtr root){
	while(root->left != tree->NIL)
		root = root->left;
	return root;
}

/*
 * Function: rbtree_max
 * Purpose: This function returns the node having the maximum value in the subtree rooted at "root"
 * Input:
 *	RBTreePtr tree: The tree to search on
 *	RBTreeNodePtr root: The root of the tree to begin the search
 */
RBTreeNodePtr rbtree_max(RBTreePtr tree, RBTreeNodePtr root){
	while(root->right != tree->NIL)
		root = root->right;
	return root;
}

RBTreeNodePtr rbtree_successor(RBTreePtr tree, RBTreeNodePtr node){
	if(node->right != tree->NIL)
		return rbtree_min(tree, node->right);
	RBTreeNodePtr parent = node->parent;
	while(parent != tree->NIL && node == parent->right){
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

RBTreeNodePtr rbtree_predecessor(RBTreePtr tree, RBTreeNodePtr node){
	if(node->left != tree->NIL)
		return rbtree_max(tree, node->left);
	RBTreeNodePtr parent = node->parent;
	while(parent != tree->NIL && node == parent->left){
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

void rbtree_insert(RBTreePtr tree, RBTreeNodePtr node, int (*comp)(void*, void*)){
	RBTreeNodePtr parent = tree->NIL;
	RBTreeNodePtr current = tree->root;
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
	node->color = RBRED;
	rb_insert_fixup(tree, node);
}

void rb_insert_fixup(RBTreePtr tree, RBTreeNodePtr node){
	while((node->parent)->color == RBRED){
		if ((node->parent) == (((node->parent)->parent)->left)){
			RBTreeNodePtr uncle = ((node->parent)->parent)->right;
			if (uncle->color == RBRED){
				(node->parent)->color = RBBLACK;
				uncle->color = RBBLACK;
				((node->parent)->parent)->color = RBRED;
				node = (node->parent)->parent;
			}
			else {
				if (node == (node->parent)->right){
					node = node->parent;
					left_rotate(tree, node);
				}
				(node->parent)->color = RBBLACK;
				((node->parent)->parent)->color = RBRED;
				right_rotate(tree, (node->parent)->parent);
			}
		}
		else {
			RBTreeNodePtr uncle = ((node->parent)->parent)->left;
			if (uncle->color == RBRED){
				(node->parent)->color = RBBLACK;
				uncle->color = RBBLACK;
				((node->parent)->parent)->color = RBRED;
				node = (node->parent)->parent;
			}
			else {
				if (node == (node->parent)->left){
					node = node->parent;
					right_rotate(tree, node);
				}
				(node->parent)->color = RBBLACK;
				((node->parent)->parent)->color = RBRED;
				left_rotate(tree, (node->parent)->parent);
			}
		}
	}
	(tree->root)->color = RBBLACK;
}

void transplant(RBTreePtr tree, RBTreeNodePtr current, RBTreeNodePtr next){
	if (current->parent == tree->NIL)
		tree->root = next;
	else if ((current->parent)->left == current)
		(current->parent)->left = next;
	else if ((current->parent)->right == current)
		(current->parent)->right = next;
	next->parent = current->parent;
}

void rbtree_delete(RBTreePtr tree, RBTreeNodePtr node){
	/*
	 * This function is implemented as described in CLRS Algorithm
	 * The nodes x, y and z referred in the CLRS book are here
	 * referred as successor_child, successor and node.
	 */

	RBTreeNodePtr successor = node;
	RBTreeNodePtr successor_child;
	int successor_original_color = successor->color;

	if (node->left == tree->NIL){
		successor_child = node->right;
		transplant(tree, node, node->right);
	}
	else if (node->right == tree->NIL){
		successor_child = node->left;
		transplant(tree, node, node->left);
	}
	else {
		successor = rbtree_min(tree, node->right);
		successor_original_color = successor->color;
		successor_child = successor->right;
		if (successor == node->right){
			successor_child->parent = successor;
		}

		else {
			transplant(tree, successor, successor->right);
			successor->right = node->right;
			(successor->right)->parent = successor;
		}
		transplant(tree, node, successor);
		successor->left = node->left;
		(successor->left)->parent = successor;
		successor->color = node->color;
	}
	if (successor_original_color == RBBLACK)
		rb_delete_fixup(tree, successor_child);
}

void rb_delete_fixup(RBTreePtr tree, RBTreeNodePtr node){
	/*
	 * This function is implemented as described in CLRS Algorithm book
	 * The nodes x and w referred in the CLRS book are here
	 * referred as node and sibling
	 */

	// Repeat this loop while the node we are talking about is not the root and its color is not BLACK 
	while(node != tree->root && node->color == RBBLACK){
		RBTreeNodePtr sibling;

		// If the node is the left child of its parent
		if (node == (node->parent)->left){
			
			// The sibling of this node should be right child of the parent
			sibling = (node->parent)->right;
			
			// Case 1:
			// If the sibling's color is RED do following:
			// Set the sibling's color BLACK, and the parent's color RED.
			// Left rotate the parent such that the child of its sibling (which must have been BLACK) is now the node's sibling
			// The sole purpose of this case is to transform into any other 3 cases. Now, this node has a BLACK sibling.

			if (sibling->color == RBRED){
				sibling->color = RBBLACK;
				(node->parent)->color = RBRED;
				left_rotate(tree, node->parent);
				sibling = (node->parent)->right;
			}
			
			// Case 2:
			// Note that this is NOT and else if condition. If we get inside above conditional statment, we might get into here as well.
			// The node's sibling MUST be BLACK at this point
			// If the node's sibling was RED, we would have made it BLACK in the Case 1.
			// So, if the node's sibling is BLACK and both of the children of the sibling are BLACK, then change the color of sibling to RED.
			// And set node to point to its parent.
			// Note that the subtree rooted at "node" had 1 fewer BLACK node due to rb_delete. We are now, modifying the sibling's color to RED
			// so that the height in the sibling's subtree is also decreased by 1. This way the subtree rooted at parent is now overall has 1 fewer
			// BLACK nodes. This is why now we are propagating the problem from node to its parent. Now, the while loop will continue to next iteration.
			if ((sibling->left)->color == RBBLACK && (sibling->right)->color == RBBLACK){
				sibling->color = RBRED;
				node = node->parent;
			}
			// Note that this is else condition and case 2 will not go through here, however, case 1 might.
			// The node's sibling is BLACK and both of its children are not BLACK
			else{

				// Case 3:
				// The node's sibling is BLACK and its left child is RED and its right child is BLACK
				// To do that, we color the left child of the sibling BLACK, and the sibling to RED, then we right rotate at sibling
				// We modify the coloring this so that the sibling's right child becomes red and we can proceed to case 4.
				if ((sibling->right)->color == RBBLACK){
					(sibling->left)->color = RBBLACK;
					sibling->color = RBRED;
					right_rotate(tree, sibling);
					sibling = (node->parent)->right;
				}

				// Case 4:
				// Note that Case 3 MUST pass through this case. In case 3 we modified the colors of node to make it case 4.
				// The node's sibling is BLACK and its right child is RED. The color of left child and parent does not matter.
				// Modify the sibling's color to take its parent's color and set the color of sibling's parent and right child to BLACK.
				// A left roatet at the parent should now add extra black node in the left subtree where the "node" is located.
				// This is a terminating condition, i.e. the height should be properly balanced in this case.
				// The height of subtree rooted at "node" had 1 fewer black node. Now, its parent is made black and the parent is added to the left subtree.
				// The sibling who took the parent's color now becomes the grand-parent of the node, i.e. parent of the node's parent.
				// Thus the black height is maintained.
				// Finally, we also set the node to point the root of the tree, so that the while loop terminates here.
				sibling->color = (node->parent)->color;
				(node->parent)->color = RBBLACK;
				(sibling->right)->color = RBBLACK;
				left_rotate(tree, node->parent);
				node = tree->root;
			}
		}
		// If the node is the right child of its parent
		// There are 4 symmetric cases as above. 
		else{
			sibling = (node->parent)->left;
			if (sibling->color == RBRED){
				sibling->color = RBBLACK;
				(node->parent)->color = RBRED;
				right_rotate(tree, node->parent);
				sibling = (node->parent)->left;
			}
			if ((sibling->left)->color == RBBLACK && (sibling->right)->color == RBBLACK){
				sibling->color = RBRED;
				node = node->parent;
			}
			else{
				if ((sibling->left)->color == RBBLACK){
					(sibling->right)->color = RBBLACK;
					sibling->color = RBRED;
					left_rotate(tree, sibling);
					sibling = (node->parent)->left;
				}

				sibling->color = (node->parent)->color;
				(node->parent)->color = RBBLACK;
				(sibling->left)->color = RBBLACK;
				right_rotate(tree, node->parent);
				node = tree->root;
			}
		}
	}
	node->color = RBBLACK;
}


void left_rotate(RBTreePtr tree, RBTreeNodePtr node){
	/* Left rotate uses right edge of node*/
	RBTreeNodePtr right_child = node->right;
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

void right_rotate(RBTreePtr tree, RBTreeNodePtr node){
	/* Right rotate uses left edge of node */
	RBTreeNodePtr left_child = node->left;
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
