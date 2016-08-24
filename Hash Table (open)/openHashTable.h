#ifndef OPENHASHTABLE
#define OPENHASHTABLE

#include <stdlib.h>
#include<stdio.h>
#include<assert.h>

#ifndef TYPE
#define TYPE int
#endif

struct openHashTable {
	TYPE ** table;
	int tablesize;
	int count;
};

void initOpenHashTable(struct openHashTable *, int);

int openHashTableSize(struct openHashTable *);

void openHashTableAdd(struct openHashTable *, TYPE *);

int openHashTableBagContains(struct openHashTable *, TYPE);

void _resizeOpenHashTable(struct openHashTable *);	//comment out for production...

#endif