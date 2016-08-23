#include<stdio.h>
#include<stdlib.h>
#include "avl.h"


/* Example main file to begin exercising your tree */
int main(int argc, char *argv[]) {	
	struct AVLTree *tree = newAVLTree();		

	/*Create values of the type of data that you want to store*/
	struct data myData1, myData2, myData3, myData4, myData5, myData6, myData7, myData8;
	
	myData1.number = 5;
	myData1.name = "rooty";
	myData2.number = 1;
	myData2.name = "lefty";
	myData3.number = 10;
	myData3.name = "righty";
	myData4.number = 30;
	myData4.name = "righty";
	myData5.number = 20;
	myData5.name  = "lefty";
	
	
	myData1.number = 30;
	myData1.name = "rooty";
	myData2.number = 20;
	myData2.name = "second";
	myData3.number = 50;
	myData3.name = "third";
	myData4.number = 40;
	myData4.name = "fourth";
	myData5.number = 60;
	myData5.name  = "fifth";
	myData6.number = 70;
	myData6.name  = "sixth";


	myData1.number = 50;
	myData1.name = "rooty";
	myData2.number = 22;
	myData2.name = "second";
	myData3.number = 80;
	myData3.name = "third";
	myData4.number = 70;
	myData4.name = "fourth";
	myData5.number = 75;
	myData5.name  = "fifth";
	myData6.number = 73;
	myData6.name  = "sixth";

	myData1.number = 75;
	myData1.name = "rooty";
	myData2.number = 70;
	myData2.name = "second";
	myData3.number = 100;
	myData3.name = "third";
	myData4.number = 60;
	myData4.name = "fourth";
	myData5.number = 80;
	myData5.name  = "fifth";
	myData6.number = 105;
	myData6.name  = "sixth";
	myData7.number = 77;
	myData7.name  = "seventh";
	myData8.number = 120;
	myData8.name  = "eighth";

	/*add the values to AVL*/
	addAVLTree(tree, &myData1, compare);
	addAVLTree(tree, &myData2, compare);
	addAVLTree(tree, &myData3,compare);
	printTree(tree, printVal);
	printf("\n\n");

	addAVLTree(tree, &myData4, compare);
	printTree(tree, printVal);
	printf("\n\n");

	addAVLTree(tree, &myData5, compare);
	printTree(tree, printVal);
	printf("\n\n");

	addAVLTree(tree, &myData6, compare);
	addAVLTree(tree, &myData7, compare);
	addAVLTree(tree, &myData8, compare);

	printTree(tree, printVal);
	printf("\n\n");
	
	removeAVLTree(tree, &myData8, compare);
	removeAVLTree(tree, &myData4, compare);

	printTree(tree, printVal);
	printf("\n\n");
	
	printInorder(tree->root);
	printf("\n\n");

	freeAVLTree(tree);
	return 0;
}