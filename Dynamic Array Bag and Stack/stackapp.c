/**************************************************************************
** stackapp.c
** Author: Chris Kearns
** Stack application for validating balanced [{()}] in input
** string. See algorithm at bottom of file.
** Call from command line:	prog '[{()}]'
** Requires #include dynArray.h (Implementation of stack and bag with
** underlying array.)
**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/****************************************************************
	Using stack to check for unbalanced parentheses.
******************************************************************/

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre:	s is not null		
*/
char nextChar(char* s) {
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string. 	
	pre:	s is not null.
	post:	Stack is deleted and we return res.
	ret:	int 1 for true, 0 for false.
*/
int isBalanced(char* s) {
	DynArr *dyn;
	dyn = newDynArr(12);	/* arbitrarily selected array size. */
	char r;
	int res = 0;

	do {
		r = nextChar(s);
		if (r == '{' || r == '(' || r == '[') {
			if (r == '{') r = '}';
			if (r == '[') r = ']';
			if (r == '(') r = ')';
			pushDynArr(dyn, r);
		}
		else if (r == '}' || r == ']' || r == ')') {
			if (isEmptyDynArr(dyn)) {
				res = 0;
				deleteDynArr(dyn);
				return res;
			}
			else if(topDynArr(dyn) == r) {
				popDynArr(dyn);
			}
		}
	} while (r != '\0');

	if (isEmptyDynArr(dyn)) {
		res = 1;
	}

	deleteDynArr(dyn);
	return res;
}


int main(int argc, char* argv[]){
	if (argv[1] != NULL) {
		char* s = argv[1];
		int res;
	
		printf("Assignment 2\n");
		res = isBalanced(s);
		if (res)
			printf("The string %s is balanced\n",s);
		else 
			printf("The string %s is not balanced\n",s);
	}
	else {
		printf("\"prog\" needs an argument such as prog '' or prog '[{()}]'\n");
	}
	return 0;
}
