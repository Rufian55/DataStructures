#include "OrderedBag.h"
#include "DynArray.h"

void _dynArrayDoubleCapacity(struct DynArr *da) {
	TYPE *newData;
	newData = malloc(sizeof(TYPE) * 2);
	assert(newData != 0);
	int newCap = da->capacity * 2;
	int count;
	for (count = 0; count < da->capacity; ++count)
		newData[count] = da->data[count];
	free(da->data);
	da->data = newData;
	da->capacity = newCap;
}

void orderedArrayAdd(struct DynArr *da, TYPE newElement) {
	int index = binarySearch(da->data, da->size, newElement);
	dynArrayAddAt(da, index, newElement);
}

void dynArrayAddAt(struct DynArr *da, int index, TYPE newElement) {
	int i;
	assert(index >= 0 && index <= da->size);
	if (da->size >= da->capacity)
		_dynArrayDoubleCapacity(da);
	
	for (i = da->size; i >= index; i--) {
		da->data[i + 1] = da->data[i];
	}
	da->data[index] = newElement;
	da->size++;
}

/* Returns index value of testValue if found or, if not found,
   the index position where testValue could be inserted and 
   preserve order. */
int dynArrayBinarySearch(struct DynArr * da, TYPE testValue) {
	return binarySearch(da->data, da->size, testValue);
}

int orderedArrayContains(struct DynArr *da, TYPE testElement) {
	return dynArrayBinarySearch(da, testElement);
}

void orderedArrayRemove(struct DynArr *da, TYPE testElement) {
	if (orderedArrayContains(da, testElement) < da->size) {
		int index = binarySearch(da->data, da->size, testElement);
		removeAtDynArr(da, index);
	}
}

int main(int argc, char* argv[]) {
	struct DynArr anArray;
	struct DynArr *da;
	da = &anArray;
	initDynArr(da, 5);
	int i;

	orderedArrayAdd(da, 10);
	orderedArrayAdd(da, 20);
	orderedArrayAdd(da, 30);

	for (i = 0; LT(i, da->size); i++)
		printf("data[%d] = %d\n", i, getDynArr(da, i));

	printf("orderedArrayContains(da, 10) reports idx pos: %d\n", orderedArrayContains(da, 10));
	printf("orderedArrayContains(da, 20) reports idx pos: %d\n", orderedArrayContains(da, 20));
	printf("orderedArrayContains(da, 30) reports idx pos: %d\n", orderedArrayContains(da, 30));

	orderedArrayAdd(da, 15);

	for (i = 0; LT(i, da->size); i++)
		printf("data[%d] = %d\n", i, getDynArr(da, i));
	printf("\n");

	orderedArrayRemove(da, 10);

	for (i = 0; LT(i, da->size); i++)
		printf("data[%d] = %d\n", i, getDynArr(da, i));
	printf("\n");

	freeDynArr(da);
	return 0;
}