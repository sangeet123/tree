/*
 * splaytree.h
 * Author: Sangeet Dahal
 */

#ifndef SPLAYTREE_H_
#define SPLAYTREE_H_

#include <stdlib.h>


/*
 * Structure for a tree node.
 * It contains following elements:
 * data - A character pointer to hold string data
 * right - A tree node pointer to right child
 * left - A tree node pointer to left child
 * parent - A tree node pointer to its parent
 */
typedef struct tnode* SplayTreeNodePtr;
typedef struct tnode {
	void *data;
	SplayTreeNodePtr right;
	SplayTreeNodePtr left;
	SplayTreeNodePtr parent;	
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
typedef struct tree* SplayTreePtr;
typedef struct tree {
	SplayTreeNodePtr root;
	SplayTreeNodePtr NIL;
} Tree;

/*
 * Function declarations
 */
SplayTreeNodePtr splaytree_node_allocate(SplayTreePtr tree);
SplayTreePtr splaytree_allocate(void);
void inorder_splaytree_walk_depth(SplayTreePtr tree, SplayTreeNodePtr root, int depth, char* (*get_string)(void *));
void inorder_splaytree_walk(SplayTreePtr tree, SplayTreeNodePtr root, char* (*get_string)(void *));
void preorder_splaytree_walk(SplayTreePtr tree, SplayTreeNodePtr root, char* (*get_string)(void *));
void postorder_splaytree_walk(SplayTreePtr tree, SplayTreeNodePtr root, char* (*get_string)(void *));
void bfs_splaytree_walk(SplayTreePtr tree, char* (*get_string)(void *));
SplayTreeNodePtr splaytree_search(SplayTreePtr tree, SplayTreeNodePtr root, void *data, int (*comp)(void*, void*));
SplayTreeNodePtr splaytree_min(SplayTreePtr tree, SplayTreeNodePtr root);
SplayTreeNodePtr splaytree_max(SplayTreePtr tree, SplayTreeNodePtr root);
SplayTreeNodePtr splaytree_successor(SplayTreePtr tree, SplayTreeNodePtr node);
SplayTreeNodePtr splaytree_predecessor(SplayTreePtr tree, SplayTreeNodePtr node);
void splaytree_insert(SplayTreePtr tree, SplayTreeNodePtr node, int (*comp)(void*, void*));
void splay(SplayTreePtr tree, SplayTreeNodePtr node);
void transplant(SplayTreePtr tree, SplayTreeNodePtr current, SplayTreeNodePtr next);
void splaytree_delete(SplayTreePtr tree, SplayTreeNodePtr node);
void left_rotate(SplayTreePtr tree, SplayTreeNodePtr node);
void right_rotate(SplayTreePtr tree, SplayTreeNodePtr node);


#endif
