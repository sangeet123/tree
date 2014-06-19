/*
 * rbtree.h
 * Author: Sangeet Dahal
 * Created: Jan 06, 2014
 */

#ifndef RBrbtree_H_
#define RBrbtree_H_

#include <stdlib.h>

#define RBRED 1
#define RBBLACK 0


/*
 * Structure for a tree node.
 * It contains following elements:
 * data - A character pointer to hold string data
 * right - A tree node pointer to right child
 * left - A tree node pointer to left child
 * parent - A tree node pointer to its parent
 * color - An integer value. RBRED = 1, for RED color. RBBLACK = 0 for black node
 */
typedef struct tnode* RBTreeNodePtr;
typedef struct tnode {
	void *data;
	RBTreeNodePtr right;
	RBTreeNodePtr left;
	RBTreeNodePtr parent;
	int color;	
} Treenode;

/*
 * Structure for a tree.
 * It contains following elements:
 * root - A tree node pointer to point the root of the tree.
 * NIL - A tree node pointer used to represent sentinel T.nil. T.nil is used as defined in CLRS book.
 * 
 * NOTE: Tree structure is used here for convenience, so that the root of the node can easily be tracked.
 * Also, the sentinel NIL is actually a tree node pointer with string "NIL" set as its data.
 */
typedef struct tree* RBTreePtr;
typedef struct tree {
	RBTreeNodePtr root;
	RBTreeNodePtr NIL;
} Tree;

/*
 * Function declarations
 */
RBTreeNodePtr rbtree_node_allocate(RBTreePtr tree);
RBTreePtr rbtree_allocate(void);
void inorder_rbtree_walk_depth(RBTreePtr tree, RBTreeNodePtr root, int depth, char* (*get_string)(void *));
void inorder_rbtree_walk(RBTreePtr tree, RBTreeNodePtr root, char* (*get_string)(void *));
void preorder_rbtree_walk(RBTreePtr tree, RBTreeNodePtr root, char* (*get_string)(void *));
void postorder_rbtree_walk(RBTreePtr tree, RBTreeNodePtr root, char* (*get_string)(void *));
void bfs_rbtree_walk(RBTreePtr tree, char* (*get_string)(void *));
RBTreeNodePtr rbtree_search(RBTreePtr tree, RBTreeNodePtr root, void *data, int (*comp)(void*, void*));
RBTreeNodePtr rbtree_min(RBTreePtr tree, RBTreeNodePtr root);
RBTreeNodePtr rbtree_max(RBTreePtr tree, RBTreeNodePtr root);
RBTreeNodePtr rbtree_successor(RBTreePtr tree, RBTreeNodePtr node);
RBTreeNodePtr rbtree_predecessor(RBTreePtr tree, RBTreeNodePtr node);
void rbtree_insert(RBTreePtr tree, RBTreeNodePtr node, int (*comp)(void*, void*));
void rb_insert_fixup(RBTreePtr tree, RBTreeNodePtr node);
void transplant(RBTreePtr tree, RBTreeNodePtr current, RBTreeNodePtr next);
void rbtree_delete(RBTreePtr tree, RBTreeNodePtr node);
void left_rotate(RBTreePtr tree, RBTreeNodePtr node);
void right_rotate(RBTreePtr tree, RBTreeNodePtr node);
void rb_delete_fixup(RBTreePtr tree, RBTreeNodePtr node);

#endif	/* RBrbtree_H_ */
