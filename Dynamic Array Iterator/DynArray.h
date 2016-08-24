#ifndef DYNARRAY
#define DYNARRAY

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#ifndef TYPE
#define TYPE int
#endif

# ifndef EQ
# define EQ(a, b) (a == b)
# endif

#ifndef LT
#define LT(a, b) (a < b)
#endif

#ifndef GT
#define GT(a, b) (a > b)
#endif

struct DynArr {
	TYPE * data;	// Pointer to the data array.
	int size;	// Number of elements in the array.
	int capacity;	// Capcity of the array.
};

void initDynArr(struct DynArr *, int);

void _setCapacityDynArr(struct DynArr *);

void freeDynArr(struct DynArr *);

TYPE sizeDynArr(struct DynArr *);

void addDynArr(struct DynArr *, TYPE);

void removeAtDynArr(struct DynArr *, int);

TYPE getDynArr(struct DynArr *, int);

void putDynArr(struct DynArr *, int, TYPE);

void removeDynArr(struct DynArr *, TYPE);

int containsDynArr(struct DynArr *, TYPE);

#endif
