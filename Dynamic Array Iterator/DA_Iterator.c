#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "DA_Iterator.h"
#include "DynArray.h"


/* Initializes a given iterator by setting it to the first
element in our dynamic array and setting the index to 0 */
void dynArrayIteratorInit(struct DynArr *da, struct dynArrayIterator *itr) {
	itr->da = da;
	itr->currentIndex = -1;
}


/* Test the currentIndex against the size of the array. */
int dynArrayIteratorHasNext(struct dynArrayIterator *itr) {
	if ((itr->da->size - itr->currentIndex) > 1)
		return 1;
	else
		return 0;
}


/* Make sure we have a place to jump to, then jump to it and return the value. */
TYPE dynArrayIteratorNext(struct dynArrayIterator *itr) {
	/* Make sure we have a next to jump to first. */
	assert(dynArrayIteratorHasNext(itr));
	itr->currentIndex++;
	return itr->da->data[itr->currentIndex];
}


/* Remove the element at the current index and take a
step back in our index so we don't skip a value. */
void dynArrayIteratorRemove(struct dynArrayIterator *itr) {
	assert(itr->currentIndex >= 0 && itr->currentIndex < itr->da->size);
	removeAtDynArr(itr->da, itr->currentIndex);
	itr->currentIndex--;
}

int main(int argc, char* argv[]) {
	struct DynArr realArray;
	struct DynArr *bag = NULL;
	bag = &realArray;
	initDynArr(bag, 2);

	addDynArr(bag, 10);
	addDynArr(bag, 20);
	addDynArr(bag, 30);

	int i;
	for (i = 0; LT(i, bag->size); i++) {
		printf("bag[%d]= %d\n", i, bag->data[i]);
	}

	struct dynArrayIterator itr;
	TYPE current;

	dynArrayIteratorInit(bag, &itr);
	printf("dynArrayIteratorHasNext reports: %d\n", dynArrayIteratorHasNext(&itr));

	while (dynArrayIteratorHasNext(&itr)) {
		current = dynArrayIteratorNext(&itr);
		printf("current = %d\n", current);
		dynArrayIteratorRemove(&itr);
	}

	printf("\n");

	for (i = 0; LT(i, bag->size); i++) {
		printf("bag[%d]= %d\n", i, bag->data[i]);
	}

	freeDynArr(bag);
	return 0;
}