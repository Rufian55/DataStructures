/* AVLTreeSort.c - Tree Sort (on AVL tree w/ dynamic array) */

/* Sort values in array data - treeSort takes data array
   and adds each element to an AVLtree. treeSortHelper
   then recursively performs an in order traversal to 
   copy the now sorted elements back to data array.
 * param - data: an array to be sorted.
 * Param - n:	  capacity of data.
*/
void treeSort(TYPE *data, int n) {
	AVLtree tree;
	int i;
	int count = 0;
	initAVLTree(&tree);
	for (i = 0; i < n ; i++) {
		addAVLTree(&tree, data[i]);
	}
	_treeSortHelper(tree­>root, data, &count);
}

/* Performs an inorder traversal of the AVLtree recursively
   copying the node values back to the data array.
*/
_treeSortHelper(AVLNode *cur, TYPE *data, int *count) {
	if (cur != 0) {
		_treeSortHelper(cur->left, data, count);
		data[*count] = cur­->val;
		*count += 1;
		_treeSortHelper(cur­->rght, data, count);
	}
}