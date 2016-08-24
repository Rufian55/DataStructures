#ifndef HASHTABLE
#define HASHTABLE

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

#ifndef TYPE
#define TYPE int
#endif

struct hlink {
	TYPE value;
	struct hlink *next;
} hashLink;

struct hashTable {
	struct hlink ** table;
	int tablesize;
	int count;
};

void initHashTable(struct hashTable *, int);

int sizeHashTable(struct hashTable *);

void addHashTable(struct hashTable *, TYPE);

int containsHashTable(struct hashTable *, TYPE);

void removeHashTable(struct hashTable *, TYPE);

#endif