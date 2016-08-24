#include "avl.h"

void initAVLTree(struct AVLTree *tree) {
   tree->root = 0;
   tree->cnt = 0;
}

struct AVLTree *newAVLTree() {
   struct AVLTree *tree;

   tree = (struct AVLTree *)malloc(sizeof(struct AVLTree));
   assert(tree != 0);

   initAVLTree(tree);
   return tree;

}

/* Prototypes for private functions */
int _height(struct AVLNode *cur);
void _setHeight(struct AVLNode *cur);
int _bf(struct AVLNode *cur);

struct AVLNode *_balance(struct AVLNode *cur);
struct AVLNode *_rotateLeft(struct AVLNode *cur);
struct AVLNode *_rotateRight(struct AVLNode *cur);

void _treeSortHelper(struct AVLNode *cur, TYPE *, int *);

/* Memeory Management Functions. */

void _freeAVLTree(struct AVLNode *node) {
  if (node != 0) {
    _freeAVLTree(node->left);
    _freeAVLTree(node->rght);
     free(node);
  }
}

void clearAVLTree(struct AVLTree *tree) {
  _freeAVLTree(tree->root);
  tree->root = 0;
  tree->cnt  = 0;

}

void freeAVLTree(struct AVLTree *tree) {
  clearAVLTree(tree);
  free(tree);
}
/* End... */


int isEmptyAVLTree(struct AVLTree *tree) {
	return tree->cnt == 0;
}

int sizeAVLTree(struct AVLTree *tree) {
	return tree->cnt;
}


struct AVLNode *_addNode(struct AVLNode *cur, void * val, comparator compare) {
	struct AVLNode *newNode;
	if(cur == 0) {/* Base Case */
		/* Create a new one and return it */
		newNode = (struct AVLNode *)malloc(sizeof(struct AVLNode));
		assert(newNode != 0);
		newNode->left = newNode->rght = 0;
		newNode->val = val;
		newNode->hght = 0; /* or SetHeight on new Node */
		return newNode;  /* No need to balance here! */
	}
	else { /* Recursive case */
		if((*compare)(val, cur->val) < 0)
		cur->left = _addNode(cur->left, val, compare); /* functional approach, rebuild subtree */
		else cur->rght = _addNode(cur->rght, val, compare);
	}
	/* Must balance the tree on way up from the recursion */
	return _balance(cur); /* Return the 'rebuilt' tree as return from recursion */
}

void addAVLTree(struct AVLTree *tree, void * val, comparator compare) {
	tree->root = _addNode(tree->root, val, compare); /* call the recursive helper function */
	tree->cnt++;
}

// Iterative version of contains
int containsAVLTree(struct AVLTree *tree, void * val, comparator compare) {
	struct AVLNode *cur;
	cur = tree->root;
	while(cur != 0) {
		if((*compare)(cur->val, val) == 0)
			return 1;
		else if((*compare)(val, cur->val) < 0)
			cur = cur->left;
		else cur = cur->rght;
	}
	return 0;
}


void * _leftMost(struct AVLNode *cur) {
	while(cur->left != 0) {
		cur = cur->left;
	}
	return cur->val;
}

struct AVLNode *_removeLeftmost(struct AVLNode *cur) {
	struct AVLNode *temp;
	if(cur->left != 0) {
		cur->left = _removeLeftmost(cur->left);
      return cur;
	}
	temp = cur->rght;
	free(cur);
	return temp;
}


struct AVLNode *_removeNode(struct AVLNode *cur, void * val, comparator compare) {
	struct AVLNode *temp;
	if((*compare)(val, cur->val) == 0) {
		if(cur->rght != 0) {
			cur->val = _leftMost(cur->rght);
			cur->rght =_removeLeftmost(cur->rght);
		}
		else {
			temp = cur->left;
			free(cur);
			return temp; /* Note that height could not have changed on temp */
		}
	}
	else if((*compare)(val, cur->val) < 0)
		cur->left  = _removeNode(cur->left, val, compare);
	else
		cur->rght = _removeNode(cur->rght, val, compare);
	return _balance(cur);
}


void removeAVLTree(struct AVLTree *tree, void * val, comparator compare) {
	if (containsAVLTree(tree, val, compare)) {
		tree->root = _removeNode(tree->root, val, compare);
		tree->cnt--;
	}
}


/* utility function to determine the height of a node */
int _height(struct AVLNode *cur) {
	if (cur == 0) return -1;
		return cur->hght;
}


/* Utility function to set the height of a node */
void _setHeight(struct AVLNode *cur) {
	int lh = _height(cur->left);
	int rh = _height(cur->rght);
	if (lh < rh) cur->hght = rh + 1;
		else cur->hght = lh + 1;
}


/* Utility function to compute the balance factor of a node
	computed as rght - left
*/
int _bf(struct AVLNode *cur) {
	return _height(cur->rght) - _height(cur->left);
}


/* Utility function to balance a node. */
struct AVLNode *_balance(struct AVLNode *cur) {
	/* Compute the balance factor for the node*/
	int cbf = _bf(cur);
	if (cbf < -1) { /* cur is heavy on the left */
		if (_bf(cur->left) > 0) /* Check for double rotation. ie. is the left Child heavy on the right */
			cur->left = _rotateLeft(cur->left);  /* Yes, left child was heavy on right, so rotate child's left first */
		return _rotateRight(cur); /* Rotate cur to the right*/
	}
	else if (cbf > 1) {/* Mirrors above.*/
		if (_bf(cur->rght) < 0)
			cur->rght = _rotateRight(cur->rght);
		return _rotateLeft(cur);
	}
	else {//If no rotations necessary, still have to set height for current!
		_setHeight(cur);
		return cur;
	}
}


struct AVLNode *_rotateLeft(struct AVLNode *cur) {
	struct AVLNode *newTop;
	newTop = cur->rght;
	cur->rght = newTop->left;
	newTop->left = cur;
	/* reset the heights for all nodes that have changed heights*/
	/* Note that subtrees under it are all ok...because we've worked from the bottom up */
	_setHeight(cur);
	_setHeight(newTop);
	return newTop;
}


struct AVLNode *_rotateRight(struct AVLNode *cur){
	struct AVLNode *newTop;
	newTop = cur->left;
	cur->left = newTop->rght;
	newTop->rght = cur;

	_setHeight(cur);
	_setHeight(newTop);
	return newTop;
}


/* Given a binary tree, print its node vlaues in order. */
void printInorder(struct AVLNode* cur) {
	if (cur == NULL)
		return;

	/* first recur on left child */
	printInorder(cur->left);

	/* then print the data of node */
	(*printVal)(cur->val);

	/* now recur on right child */
	printInorder(cur->rght);
}


void _printTree(struct AVLNode *cur, printer printVal) {
	if (cur == 0)
		return;

	printf("(");
	_printTree(cur->left, printVal);
	/* Note that you must change this to work for your particular 'data' pointer */

	(*printVal)(cur->val);
	printf("[%d]", cur->hght);

	_printTree(cur->rght, printVal);
	printf(")");
}


void printTree(struct AVLTree *tree, printer printVal){
	_printTree(tree->root, printVal);
}
