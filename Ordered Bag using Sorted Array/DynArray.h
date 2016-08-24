#ifndef DYNARRAY
#define DYNARRAY

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#ifndef TYPE
#define TYPE int
#endif

#ifndef LT
#define LT(a,b) (a < b)
#endif


struct DynArr {
	TYPE *data;	/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity of the array */
};

void initDynArr(struct DynArr *, int);

void freeDynArr(struct DynArr *);

int sizeDynArr(struct DynArr *);

void addDynArr(struct DynArr *, TYPE);

void _setCapacityDynArr(struct DynArr *, int);

TYPE getDynArr(struct DynArr *, int);

void putDynArr(struct DynArr *, int, TYPE);

void swapDynArr(struct DynArr *, int, int);

void removeAtDynArr(struct DynArr *, int);

int binarySearch(TYPE *, int, TYPE);

#endif