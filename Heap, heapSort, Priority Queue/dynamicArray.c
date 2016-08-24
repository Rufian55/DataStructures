/* Min Heap Implementation via Dynamic Array
 * Includes heap, stack, bag, ordered bag, and iterator functionality.
 * dynamicArray.c
 * Author: Chris Kearns
 * Date: 22 May 2016
 */

#include "dynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define TESTING

#ifndef TESTING
static void adjustHeap(DynamicArray* heap, int last, int position, compareFunction compare);
static void buildHeap(DynamicArray* heap, compareFunction compare);
#endif

struct DynamicArray {
	TYPE* data;
	int size;
	int capacity;
};

// --- Dynamic array ---

static void setCapacity(DynamicArray* array, int capacity) {
	TYPE* data = malloc(sizeof(TYPE) * capacity);
	int i;
	for (i = 0; i < array->size; i++) {
		data[i] = array->data[i];
	}
	free(array->data);
	array->data = data;
	array->capacity = capacity;
}

static void init(DynamicArray* array, int capacity) {
	assert(capacity > 0);
	array->data = NULL;
	array->size = 0;
	setCapacity(array, capacity);
}

DynamicArray* dyNew(int capacity) {
	DynamicArray* array = malloc(sizeof(DynamicArray));
	init(array, capacity);
	return array;
}

void dyDelete(DynamicArray* array) {
	free(array->data);
	free(array);
}

/* Inserts value at end of array and doubles capacity if needed. */
void dyAdd(DynamicArray* array, TYPE value) {
	if (array->size >= array->capacity) {
		setCapacity(array, 2 * array->capacity);
	}
	array->data[array->size] = value;
	array->size++;
}

/* Inserts value at postion and re-indexes array. */
void dyAddAt(DynamicArray* array, TYPE value, int position) {
	assert(position <= array->size);
	dyAdd(array, value);
	int i;
	for (i = array->size - 1; i > position; i--) {
		dySwap(array, i, i - 1);
    }
}

/* Overwrites at position with value. */
void dyPut(DynamicArray* array, TYPE value, int position) {
	assert(position < array->size);
	array->data[position] = value;
}

/* Removes value at position and reindexes array. */
void dyRemoveAt(DynamicArray* array, int position) {
	assert(position < array->size);
	int i;
	for (i = position; i < array->size - 1; i++) {
		array->data[position] = array->data[position + 1];
	}
	array->size--;
}

/* Returns value at position paramter in array. */
TYPE dyGet(DynamicArray* array, int position) {
	assert(position < array->size);
	return array->data[position];
}

/* Returns the size of the array */
int dySize(DynamicArray* array) {
	return array->size;
}

/* Swaps postion1 with postion2 and vice versa. */
void dySwap(DynamicArray* array, int position1, int position2) {
	assert(position1 < array->size);
	assert(position2 < array->size);
	TYPE temp = array->data[position1];
	array->data[position1] = array->data[position2];
	array->data[position2] = temp;
}


// --- Stack ---

void dyStackPush(DynamicArray* stack, TYPE value) {
    dyAdd(stack, value);
}

void dyStackPop(DynamicArray* stack) {
	dyRemoveAt(stack, stack->size - 1);
}

TYPE dyStackTop(DynamicArray* stack) {
	return dyGet(stack, stack->size - 1);
}

int dyStackIsEmpty(DynamicArray* stack) {
	return stack->size == 0;
}

// --- Bag ---

static int findFirst(DynamicArray* array, TYPE value, compareFunction compare) {
	int i;
	for (i = 0; i < array->size; i++) {
		if (compare(value, array->data[i]) == 0) {
			return i;
		}
	}
	return -1;
}

void dyBagAdd(DynamicArray* bag, TYPE value) {
	dyAdd(bag, value);
}

void dyBagRemove(DynamicArray* bag, TYPE value, compareFunction compare) {
	int position = findFirst(bag, value, compare);
	if (position != -1) {
		dyRemoveAt(bag, position);
	}
}

int dyBagContains(DynamicArray* bag, TYPE value, compareFunction compare) {
	return findFirst(bag, value, compare) != -1;
}

// --- Ordered bag ---

static int binarySearch(DynamicArray* array, TYPE value, compareFunction compare) {
	int low = 0;
	int high = array->size - 1;
	int middle;
	while (low <= high) {
		middle = (low + high) / 2;
		if (compare(value, array->data[middle]) < 0) {
			high = middle - 1;
		}
		else if (compare(value, array->data[middle]) > 0) {
			low = middle + 1;
		}
		else {
			return middle;
		}
	}
	return low;
}

void dyOrderedAdd(DynamicArray* bag, TYPE value, compareFunction compare) {
	int position = binarySearch(bag, value, compare);
	dyAddAt(bag,value, position);
}

void dyOrderedRemove(DynamicArray* bag, TYPE value, compareFunction compare) {
	int position = binarySearch(bag, value, compare);
	if (compare(value, bag->data[position]) == 0) {
		dyRemoveAt(bag, position);
	}
}

int dyOrderedContains(DynamicArray* bag, TYPE value, compareFunction compare) {
	int position = binarySearch(bag, value, compare);
	return compare(value, dyGet(bag, position)) == 0;
}

// --- Heap ---

/**
 * Adjusts heap to maintain the heap min property via recursive percolate down.
 * @param heap:	The array representing the heap structure.
 * @param last:	index to adjust up to.
 * @param position:	index where adjustment starts.
 * @param compare:	pointer to compare function.
 */
void adjustHeap(DynamicArray* heap, int last, int position, compareFunction compare) {
	int leftChild = 2 * position + 1;	// Index position of left child.
	int rightChild = 2 * position + 2;	// Index position of right child.

	if (rightChild < last) {
		/* We have two children, so get index of smallest child. */
		int smallest = rightChild;
		if (compare(dyGet(heap, leftChild), dyGet(heap, rightChild)) == -1)
			smallest = leftChild;
		/* Compare smallest child to position, and if necessary,
		   swap and call adjustHeap with smallest. */
		if(compare(dyGet(heap, smallest), dyGet(heap, position)) == -1) {
			dySwap(heap, smallest, position);
			adjustHeap(heap, last, smallest, compare);
		}
	}
	else if (leftChild < last) {
		/* We have one child so compare child to parent and,
		   if necessary, swap and call _adjustHeap with leftChild idndex. */
		if (compare(dyGet(heap, leftChild), dyGet(heap, position)) == -1) {
				dySwap(heap, leftChild, position);
				adjustHeap(heap, last, leftChild, compare);
		}
	}
	/* Else no children, we're at the bottom, so done. */
}

/**
 * Builds a valid min heap from an arbitrary array.
 * @param heap:	array with elements in any order.
 * @param compare:  pointer to compare function.
 */
void buildHeap(DynamicArray* heap, compareFunction compare) {
	int max = dySize(heap);				// size of the array.
	int i;						// Used in for loop to find the last non leaf node.
	for (i = max/2-1; i >= 0; i--) {
		adjustHeap(heap, max, i, compare);	// and adjustHeap on that node against the whole array.
	}
}

/**
 * Adds an element to last position in heap and percolates it up.
 * @param heap:	The underlying array.
 * @param value:	Object or Value to be added to heap.
 * @param compare:	Pointer to compare function.
*/
void dyHeapAdd(DynamicArray* heap, TYPE value, compareFunction compare) {
	int parent;				// The parent of the next open element.
	int position = dySize(heap);		// The index of the next open element in the heap array (array size).
	dyAdd(heap, value);			// Adds value at next open position and resets capacity if necessary.

	/* Percolate up */
	while (position != 0) {							// while != to the first element in the array.
		parent = (position - 1) / 2;					// Compute parent index.
		if (compare(dyGet(heap, position), dyGet(heap, parent)) == -1) { // If position < parent,
			dySwap(heap, parent, position);				// swap them,
			position = parent;					// Update position & keep percolating up.
		}
		else return;
	}
}

/**
 * Removes the first element, which has the min priority, from the heap.
 * @param heap:	The underlying array.
 * @param compare:	Pointer to the compare function.
 */
void dyHeapRemoveMin(DynamicArray* heap, compareFunction compare) {
	int last = dySize(heap) - 1;
	assert(last >= 0);			// Test harness runs it all the way down to 0.
	dyPut(heap, dyGet(heap, last), 0);	// Gets the last element and overwrites it at min.
	dyRemoveAt(heap, last);			// Removes last element.
	adjustHeap(heap, last, 0, compare);	// Puts the heap back into min order.
}

/**
 * Returns the first element, which has the min priority, from the heap.
 * @param heap
 * @return  Element at the top of the heap.
 */
TYPE dyHeapGetMin(DynamicArray* heap) {
	return dyGet(heap, 0);
}

/**
 * Sorts arbitrary array in-place - yields a reverse sort of O(n log n).
 * @param heap:	array with elements in arbitrary order.
 * @param compare:	pointer to the compare function.
 */
void dyHeapSort(DynamicArray* heap, compareFunction compare) {
	buildHeap(heap, compare);
	int i;
	for (i = dySize(heap) - 1; i > 0; i--) {
		dySwap(heap, 0, i);
		adjustHeap(heap, i, 0, compare);
	}
}

// --- Iterator ---

DynamicArrayIterator* dyIteratorNew(DynamicArray* array) {
	DynamicArrayIterator* iterator = malloc(sizeof(DynamicArrayIterator));
	iterator->array = array;
	iterator->current = 0;
	return iterator;
}

void dyIteratorDelete(DynamicArrayIterator* iterator) {
	free(iterator);
}

int dyIteratorHasNext(DynamicArrayIterator* iterator) {
	return iterator->current < iterator->array->size;
}

TYPE dyIteratorNext(DynamicArrayIterator* iterator) {
	TYPE value = dyGet(iterator->array, iterator->current);
	iterator->current++;
	return value;
}

void dyIteratorRemove(DynamicArrayIterator* iterator) {
	iterator->current--;
	dyRemoveAt(iterator->array, iterator->current);
}

// --- Utility ---

void dyPrint(DynamicArray* array, printFunction print) {
	printf("\nsize: %d\ncapacity: %d\n[\n", array->size, array->capacity);
	int i;
	for (i = 0; i < array->size; i++) {
		printf("%d : ", i);
		print(array->data[i]);
		printf("\n");
	}
	printf("]\n");
}

void dyCopy(DynamicArray* source, DynamicArray* destination) {
	free(destination->data);
	init(destination, source->capacity);
	int i;
	for (i = 0; i < source->size; i++) {
		destination->data[i] = source->data[i];
	}
	destination->size = source->size;
}
