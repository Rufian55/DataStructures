/*
 Similar to the compareTo method in java or the strcmp function in c. Compare
 returns an integer to tell you if the left value is greater than, less than, or
 equal to the right value. You are comparing the number variable, the char is not
 used in this version of compare.
 
 if left < right return -1
 if left > right return 1
 if left = right return 0
 */
#include "compare.h"

int compare(void *left, void *right) {
	struct data *ml,*mr;
	/* Casts! */
	ml = (struct data *)left;
	mr = (struct data *) right;
	/* Function to compare to 'data' types ...currently a number and name */
	if(ml->number < mr->number)
		return -1;
	if(ml->number > mr->number)
		return 1;
	return 0; /* ml->number == mr->number */
}

void printVal (void *val) {
	struct data * myVal = (struct data *)val;
	printf("%d ", myVal->number); 
}

void printName(void *name) {
	struct data * myVal = (struct data *)name;
	printf("%s ", myVal->name);
}

