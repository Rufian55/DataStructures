/* File: avl.h
   Interface definition of the AVL tree data structure.
 */
#ifndef __AVL_H
#define __AVL_H
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "compare.h"

#define TYPE int

struct AVLNode {
	void * val;
	struct AVLNode *left; /* Left child. */
	struct AVLNode *rght; /* Right child. */
	int hght;
};

/* Height-Balanced Binary Search Tree. */
struct AVLTree { 
	struct AVLNode *root;
	int cnt;
};

/* In C, pointer to "function" that takes argument types and returning type is specified as:
type (*function)(argtypes); */

typedef int (*comparator)(void * left, void * right);
typedef void (*printer)(void *);

/* Initialize binary search tree structure. */
void initAVLTree(struct AVLTree *tree);

/* Alocate and initialize search tree structure. */
struct AVLTree *newAVLTree();

/* Deallocate nodes in BST. */
void clearAVLTree(struct AVLTree *tree);

/* Deallocate nodes in AVL and AVL structure. */
void freeAVLTree(struct AVLTree *tree);

/*-- AVL Bag interface --*/
int isEmptyAVLTree(struct AVLTree *tree);
int sizeAVLTree(struct AVLTree *tree);

void addAVLTree(struct AVLTree *tree, void *val, comparator compare);
int containsAVLTree(struct AVLTree *tree, void *val, comparator compare);
void removeAVLTree(struct AVLTree *tree, void *val, comparator compare);

/* Utility function to print a tree */
void printTree(struct AVLTree *tree, printer printVal);

/* Utilty finction to print AVLtree in ascending order. */
void printInorder(struct AVLNode* cur);

# endif
