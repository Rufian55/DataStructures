/*******************************************************************
** DADequeue.c
** A deque implemented with a dynamic array including a wrap around
** feature that keeps the array from inappropriately resizing, in C.
** Author: Chris Kearns
** Date: 22 Aug 2016
********************************************************************/
#include "Dadequeue.h"


void _dequeSetCapacity(struct deque *d, int newCap) {
	int i,j;
	/* Create a new underlying array*/
	TYPE *newData = (TYPE*)malloc(sizeof(TYPE)*newCap);
	assert(newData != 0);

	/* copy elements to it */
	j = d->beg;
	for (i = 0; i < d->size; i++) {
		newData[i] = d->data[j];
		j = j + 1;
		if (j >= d->capacity)	// This is how it wraps around!
			j = 0;
	}

	/* Delete the old underlying array*/
	free(d->data);
	/* update capacity and size and data*/
	d->data = newData;
	d->capacity = newCap;
	d->beg = 0;
}

void dequeFree(struct deque *d) {
	free(d->data);
	d->size = 0;
	d->capacity = 0;
}

void dequeInit(struct deque *d, int initCapacity) {
	d->data = (TYPE *)malloc(initCapacity * sizeof(TYPE));
	assert(d->data != 0);
	d->size = d->beg = 0;
	d->capacity = initCapacity;
	assert(initCapacity > 0);
}

int dequeSize(struct deque *d) {
	return d->size;
}

/* Most of the time, the array will not need to be resized and this function
will only have to decrement the beginning and increment the size of the deque
which has O(1)+ execution time.
*/
void dequeAddFront(struct deque *d, TYPE newValue) {
	if (d->size >= d->capacity) {
		_dequeSetCapacity(d, 2 * (d->capacity));
	}

	if (d->size == 0) {
		d->data[d->beg] = newValue;
	}
	else {
		if (d->beg == 0) {
			d->beg = d->capacity - 1;
		}
		else {
			d->beg--;
		}
		d->data[d->beg] = newValue;
	}
	d->size++;
}

/* Most of the time, the array will not need to be resized and this function
will only have to increment the size of the deque which has O(1)+ execution time.
*/
void dequeAddBack(struct deque *d, TYPE newValue) {
	int i;
	if (d->size >= d->capacity) {
		_dequeSetCapacity(d, 2 * d->capacity);
	}
	i = (d->beg + d->size) % d->capacity;
	d->data[i] = newValue;
	d->size++;
}

/* This function will only have to return the data at one position of the
deque which has O(1) execution time.*/
TYPE dequeFront(struct deque *d) {
	assert(d->size > 0);
	return d->data[d->beg];
}

/* This function will only have to return the data at one position of
   the deque which has O(1) execution time.*/
TYPE dequeBack(struct deque *d) {
	assert(d->size > 0);
	int i;
	i = (d->beg + d->size - 1) % d->capacity;
	return d->data[i];
}

/* This function will only have to increment the beginning and decrement
   the size of the deque which has O(1) execution time.*/
void dequeRemoveFront(struct deque *d) {
	assert(d->size > 0);
	if (d->size != 1) {
		d->beg = (d->beg + 1) % d->capacity;
	}
	d->size--;
}

/* This function will only have to decrement the size of the
   deque which has O(1) execution time.*/
void dequeRemoveBack(struct deque *d) {
	assert(d->size > 0);
	d->size--;
}

int main(int argc, char* argv[]) {
	struct deque deck;
	struct deque *dq = 0;
	dq = &deck;
	dequeInit(dq, 2);

	printf("deque is intialized.\n");
	printf("dequeSize reports size = %d\n", dequeSize(dq));

	printf("Create a deque front->'76543'<-back...\n");

	printf("\nadding '5' to front...\n");
	dequeAddFront(dq, 5);
	printf("dequeSize reports size = %d\n", dequeSize(dq));
	printf("dequeFront (should be '5') reports %d\n", dequeFront(dq));
	printf("dequeBack (should also be 5) reports %d\n", dequeBack(dq));

	printf("\nadding '6' to front...\n");
	dequeAddFront(dq, 6);
	printf("dequeSize reports size = %d\n", dequeSize(dq));
	printf("dequeFront (should be '6') reports %d\n", dequeFront(dq));
	printf("dequeBack (should be 5) reports %d\n", dequeBack(dq));

	printf("\nadding '7' to front...\n");
	dequeAddFront(dq, 7);
	printf("dequeSize reports size = %d\n", dequeSize(dq));
	printf("dequeFront (should be '7') reports %d\n", dequeFront(dq));
	printf("dequeBack (should be '5') reports %d\n", dequeBack(dq));

	printf("\nadding '4' to back...\n");
	dequeAddBack(dq, 4);
	printf("dequeSize reports size = %d\n", dequeSize(dq));
	printf("dequeFront (should be '7') reports %d\n", dequeFront(dq));
	printf("dequeBack (should be '4') reports %d\n", dequeBack(dq));
	
	printf("\nadding '3' to back...\n");
	dequeAddBack(dq, 3);
	printf("dequeSize reports size = %d\n", dequeSize(dq));
	printf("dequeFront (should be '7') reports %d\n", dequeFront(dq));
	printf("dequeBack (should be '3') reports %d\n", dequeBack(dq));

	printf("\nremoving from back...\n");
	dequeRemoveBack(dq);
	printf("dequeSize reports size = %d\n", dequeSize(dq));
	printf("dequeFront (should be '7') reports %d\n", dequeFront(dq));
	printf("dequeBack (should be '4') reports %d\n", dequeBack(dq));

	printf("\nremoving from back...\n");
	dequeRemoveBack(dq);
	printf("dequeSize reports size = %d\n", dequeSize(dq));
	printf("dequeFront (should be '7') reports %d\n", dequeFront(dq));
	printf("dequeBack (should be '5') reports %d\n", dequeBack(dq));

	printf("\nremoving from back...\n");
	dequeRemoveBack(dq);
	printf("dequeSize reports size = %d\n", dequeSize(dq));
	printf("dequeFront (should be '7') reports %d\n", dequeFront(dq));
	printf("dequeBack (should be '6') reports %d\n", dequeBack(dq));

	printf("\nremoving from back...\n");
	dequeRemoveBack(dq);
	printf("dequeSize reports size = %d\n", dequeSize(dq));
	printf("dequeFront (should be '7') reports %d\n", dequeFront(dq));
	printf("dequeBack (should be '7') reports %d\n", dequeBack(dq));

	dequeFree(dq);
	return 0;
}