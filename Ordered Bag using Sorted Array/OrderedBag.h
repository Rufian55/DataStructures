#ifndef ORDEREDBAG
#define ORDEREDBAG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "OrderedBag.h"

#ifndef TYPE
#define TYPE int
#endif

void orderedArrayAdd(struct DynArr *, TYPE);

void dynArrayAddAt(struct DynArr *, int, TYPE);

int dynArrayBinarySearch(struct DynArr *, TYPE);

int orderedArrayContains(struct DynArr *, TYPE);

void orderedArrayRemove(struct DynArr *, TYPE);

#endif