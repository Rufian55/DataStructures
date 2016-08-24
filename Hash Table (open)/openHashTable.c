#include "openHashTable.h"

struct openHashTable {
	TYPE ** table;
	int tablesize;
	int count;
};

void initOpenHashTable(struct openHashTable * ht, int size) {
	int i;
	assert(size > 0);
	ht->table = (TYPE **)malloc(size * sizeof(TYPE *));
	assert(ht->table != 0);
	for (i = 0; i < size; i++)
		ht->table[i] = 0;	/* initialize empty */
	ht->tablesize = size;
	ht->count = 0;
}

int openHashTableSize(struct openHashTable *ht) {
	return ht->count;
}

void openHashTableAdd(struct openHashTable * ht, TYPE *newValue) {
	assert(ht != 0);
	int idx;

	/* Make sure we have space and under the load factor threshold. */
	if ((ht->count / (double)ht->tablesize) >= 0.75)
		_resizeOpenHashTable(ht);
	ht->count++;

	idx = HASH(newValue) % ht->tablesize;

	/* To be safe, use only positive arithmetic.  % may behave very differently on diff
	implementations or diff languages. However, you can do the following to deal with a
	negative result from the HASH function. */

	if (idx < 0)
		idx += ht->tablesize;

	/* Search through table until an empty spot is encountered. */
	while (ht->table[idx] != 0){
		idx++;
		// loop back to start of table.
		if (idx >= ht->tablesize)
			idx = 0;
	}/* Guaranteed to have an empty spot since we resized if necessary! */
	ht->table[idx] = newValue;
}


int openHashTableBagContains(struct openHashTable *ht, TYPE  newValue) {
	assert(ht != 0);
	int idx = HASH(newValue) % ht->tablesize;
	if (idx < 0)
		idx += ht->tablesize;
	// Search through table until an empty spot is encountered.
	while (ht->table[idx] != 0) {
		// value found
		if (newValue == ht->table[idx])
			return 1;
		idx++;
		// loop back to start of table.
		if (idx == ht->tablesize)
			idx = 0;
	}
	// Value not found.
	return 0;
}


void _resizeOpenHashTable(struct openHashTable *ht) {
	assert(ht != 0);

	int oldTablesize = ht->tablesize;
	ht->tablesize = 2 * (ht->tablesize);

	TYPE **oldTable = ht->table;
	/* Create a new array. */
	ht->table = (TYPE **)malloc(ht->tablesize * sizeof(TYPE *));
	assert(ht->table != 0);

	/* Rehash all elements into the new, larger table. */
	int i;
	for (i = 0; i < oldTablesize; i++)	{
		if (oldTable[i] != 0)
			openHashTableAdd(ht, oldTable[i]); /* Rehashes. */
	}
	free(oldTable);
}