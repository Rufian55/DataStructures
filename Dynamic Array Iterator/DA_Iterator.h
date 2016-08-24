#ifndef DA_ITERATOR
#define DA_ITERATOR

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

struct dynArrayIterator {
	struct DynArr * da;
	int currentIndex;
};

void dynArrayIteratorInit(struct DynArr *da, struct dynArrayIterator *itr);

int dynArrayIteratorHasNext(struct dynArrayIterator *itr);

TYPE dynArrayIteratorNext(struct dynArrayIterator *itr);

void dynArrayIteratorRemove(struct dynArrayIterator *itr);

#endif