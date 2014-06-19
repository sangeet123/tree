/*
 * File: avl.h
 * Author: Sangeet Dahal
 */

#ifndef AVL_H_
#define AVL_H_

typedef struct tnode* AVLTreeNodePtr;

typedef struct tnode {
	void *data;
	AVLTreeNodePtr right;
	AVLTreeNodePtr left;
	AVLTreeNodePtr parent;
	int height;
} Treenode;

typedef struct tree* AVLTreePtr;

typedef struct tree {
	AVLTreeNodePtr root;
	AVLTreeNodePtr NIL;
} Tree;

AVLTreeNodePtr avltree_node_allocate(AVLTreePtr tree);
AVLTreePtr avltree_allocate(void);
int get_height(AVLTreePtr tree, AVLTreeNodePtr node);
void inorder_avl_tree_walk(AVLTreePtr tree, AVLTreeNodePtr root, char* (*get_string)(void *));
void preorder_avl_tree_walk(AVLTreePtr tree, AVLTreeNodePtr root, char* (*get_string)(void *));
void postorder_avl_tree_walk(AVLTreePtr tree, AVLTreeNodePtr root, char* (*get_string)(void *));
void bfs_avltree_walk(AVLTreePtr tree, char* (*get_string)(void*));
AVLTreeNodePtr avltree_search(AVLTreePtr tree, AVLTreeNodePtr root, char *data, int (*comp)(void *, void *));
AVLTreeNodePtr avltree_min(AVLTreePtr tree, AVLTreeNodePtr root);
AVLTreeNodePtr avltree_max(AVLTreePtr tree, AVLTreeNodePtr root);
AVLTreeNodePtr tree_successor(AVLTreePtr tree, AVLTreeNodePtr node);
AVLTreeNodePtr tree_predecessor(AVLTreePtr tree, AVLTreeNodePtr node);
void avltree_insert(AVLTreePtr tree, AVLTreeNodePtr node, int (*comp)(void *, void *));
void avl_transplant(AVLTreePtr tree, AVLTreeNodePtr current, AVLTreeNodePtr next);
void avltree_delete(AVLTreePtr tree, AVLTreeNodePtr node);
inline int max(int first, int second);
void avlcalculate_height(AVLTreePtr tree, AVLTreeNodePtr node);

#endif
