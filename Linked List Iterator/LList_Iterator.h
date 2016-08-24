#ifndef LLIST_ITERATOR
#define LLIST_ITERATOR

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "LList.h"

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


struct linkedListIterator {
	struct linkedList * lst;
	struct dlink * currentLink;
};

void linkedListIteratorInit(struct linkedList  *, struct linkedListIterator *);

int linkedListIteratorHasNext(struct linkedListIterator *);

TYPE linkedListIteratorNext(struct linkedListIterator *);

void linkedListIteratorRemove(struct linkedListIterator *);

#endif