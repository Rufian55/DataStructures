/*	file: compare.c
	Chris Kearns  CS261-400-S16
	Assingment 4  7 Apr 2016
	Implementation of BST's compare functions.
*/
#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"

/*----------------------------------------------------------------------------
Very similar to the compareTo method in java or the strcmp function in c. It
 returns an integer that tells if the left value is greater than, less than, or
 equal to the right value. This compares the number variable, letter is not
 used in the comparison like this:
	if left < right return -1
	if left > right return 1
	if left = right return 0
 */

 /* Type cast the value of void * to the desired type.
    Definition of TYPE in bst.h is void*, which means that left and
    right are void pointers. To compare left and right, first cast
    left and right to the corresponding pointer type (struct data *),
    and then compare the values pointed by the casted pointers.
    DO NOT compare the addresses pointed by left and right,
    i.e. "if (left < right)".
 */
int compare(TYPE left, TYPE right) {
	struct data *myLeft, *myRight;

	myLeft = (struct data *)left;
	myRight = (struct data *) right;

	/* Function compares types - change in struct.h as needed. */
	if (myLeft->number < myRight->number)
		return -1;
	if (myLeft->number > myRight->number)
		return 1;

	return 0; /* myLeft->number == myRight->number */
}

/*Print funcction that type casts the value of void * to the desired type.
  Chagne printf %modifier to match desired print type.*/
void print_type(TYPE curval) {
	struct data * myVal = (struct data *)curval;
	printf("%d ", myVal->number);
}