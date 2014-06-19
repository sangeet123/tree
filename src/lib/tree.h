/*
 * tree.h
 * Author: Sangeet Dahal
 */

#ifndef TREE_H_
#define TREE_H_


#endif	/* TREE_H_ */

#include <stdlib.h>
#include <string.h>

typedef struct tnode* TreeNodePtr;

typedef struct tnode {
	char *word;
	TreeNodePtr right;
	TreeNodePtr left;
	TreeNodePtr parent;
	int depth;
} Treenode;

typedef struct tree* TreePtr;

typedef struct tree {
	TreeNodePtr root;
} Tree;


TreePtr tree_allocate(void){
	return (TreePtr) malloc(sizeof(Tree));
}

TreeNodePtr tree_node_allocate(void){
	return (TreeNodePtr) malloc(sizeof(Treenode));
}

void inorder_tree_walk(TreeNodePtr root){
	if (root != NULL){
		inorder_tree_walk(root->left);
		printf("%d: %s\n", root->depth, root->word);
		inorder_tree_walk(root->right);
	}
}

void preorder_tree_walk(TreeNodePtr root){
	if (root != NULL){
		printf("%s\n", root->word);
		preorder_tree_walk(root->left);
		preorder_tree_walk(root->right);
	}
}

void postorder_tree_walk(TreeNodePtr root){
	if (root != NULL){
		postorder_tree_walk(root->left);
		postorder_tree_walk(root->right);
		printf("%s\n", root->word);
	}
}

TreeNodePtr tree_search(TreeNodePtr root, char *word){
	if (root == NULL || strcmp(word, root->word) == 0)
		return root;
	if (strcmp(word, root->word) < 0)
		return tree_search(root->left, word);
	else
		return tree_search(root->right, word);
}

TreeNodePtr tree_min(TreeNodePtr root){
	while(root->left != NULL)
		root = root->left;
	return root;
}

TreeNodePtr tree_max(TreeNodePtr root){
	while(root->right != NULL)
		root = root->right;
	return root;
}

TreeNodePtr tree_successor(TreeNodePtr node){
	if(node->right != NULL)
		return tree_min(node->right);
	TreeNodePtr parent = node->parent;
	while(parent != NULL && node == parent->right){
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

TreeNodePtr tree_predecessor(TreeNodePtr node){
	if(node->left != NULL)
		return tree_max(node->left);
	TreeNodePtr parent = node->parent;
	while(parent != NULL && node == parent->left){
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

void tree_insert(TreePtr tree, TreeNodePtr node){
	
	TreeNodePtr parent = NULL;
	TreeNodePtr current = tree->root;
	while(current != NULL){
		parent = current;
		if (strcmp(node->word, current->word) <= 0)
			current = current->left;
		else
			current = current->right;
	}
	node->parent = parent;
	if (parent == NULL){
		tree->root = node;
	}
	else if (strcmp(node->word, parent->word) <= 0){
		parent->left = node;
	}
	else{
		parent->right = node;
	}
	if (parent == NULL)
		node->depth = 0;
	else
		node->depth = parent->depth + 1;
}

void transplant(TreePtr tree, TreeNodePtr current, TreeNodePtr next){
	if (current->parent == NULL)
		tree->root = next;
	else if ((current->parent)->left == current)
		(current->parent)->left = next;
	else if ((current->parent)->right == current)
		(current->parent)->right = next;
	next->parent = current->parent;
}

void tree_delete(TreePtr tree, TreeNodePtr node){
	if (node->left == NULL)
		transplant(tree, node, node->right);
	else if (node->right == NULL)
		transplant(tree, node, node->left);
	else {
		TreeNodePtr successor = tree_min(node->right);
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