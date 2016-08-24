/***************************************************************************
** BST_Iterator.c
** Author: Chris Kearns
** Date: 23 Aug 2016
** NOTE: Not needed for current BST implementation. Included here for future
** use. You  will need to include Dynamic Array with stack implementation
** found at "Dynamic Array Bag and Stack/dynArray.h & dynArray.c and then
** Binary Search Tree/bst.h & bst.c to utilize.
****************************************************************************/

struct BSTIterator {
	struct DynArr *stk;
	struct BSTree *tree;
};

void BSTIteratorInit(struct BSTree *tree, struct BSTIterator *itr) {
	//to initialize, create an empty stack
	itr->stk = newDynArr(10);
	itr->tree = tree;
}

int BSTIteratorHasNext(struct BSTIterator * itr) {
	//if stack is empty 
	if (isEmptyDynArr(itr->stk)) {
		//perform slideLeft on root 
		_slideLeft(itr->tree->root, itr);
	}
	else {
		//let n be top of stack. Pop topmost element. 
		struct Node *n = topDynArr(itr->stk);
		popDynArr(itr->stk);

		//slideLeft on right child of n 
		_slideLeft(n->right, itr);
	}

	//return true if stack is not empty 
	if (!isEmptyDynArr(itr->stk))
		return 1;
	else
		return 0;
}

TYPE BSTIteratorNext(struct BSTIterator *itr) {
	//let n be top of stack. Return value of n
	struct Node *n = topDynArr(itr->stk);
	return n->value;
}

void _slideLeft(struct Node *cur, struct BSTIterator *itr) {
	while(cur != null) {
		pushDynArr(itr->stk, cur);
		cur = cur->left;
	}
}