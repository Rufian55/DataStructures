#include"hashTable.h"

void initHashTable(struct hashTable *ht, int size) {
	int i;
	if (ht == NULL)
		return;
	ht->table = (struct hlink**)malloc(sizeof(struct hlink*) * ht->tablesize);
	assert(ht->table != 0);

	for (i = 0; i < ht->tablesize; i++)
		ht->table[i] = 0;

	ht->tablesize = size;
	ht->count = 0;
}


void addHashTable(struct hashTable *ht, TYPE newValue) {
	/* Compute hash value to find the correct bucket. */
	int hashIndex = HASH(val) % ht->tablesize;
	if (hashIndex < 0)
		hashIndex += ht->tablesize;
	struct hlink * newLink = (struct hlink *) malloc(sizeof(struct hlink));
	assert(newLink);
	newLink->value = newValue;
	newLink->next = ht->table[hashIndex];
	ht->table[hashIndex] = newLink; /* add to bucket. */
	ht->count++;
	/* Check loadFactor and resize if necessary. */
	if ((ht->count / (double)ht->tablesize) > 8.0)
		_resizeTable(ht);
}


int sizeHashTable(struct hashTable *ht) {
	return ht->count;
}


void _resizeTable(struct hashTable *ht) {
	struct hashTable oldTable = ht;
	int oldts = ht->tablesize;
	struct hlink *cur, *last;
	initHashTable(ht, 2 * oldts);
	int i;
	for (i = 0; i < oldts; i++) {
		cur = ht->table[i];
		while (cur != 0) {
			addhashTable(ht, cur->value);
			last = cur;
			cur = cur->next;
			free(last);
		}
	}
	free(oldTable);
}

/* Same as _resizeTable but using an iterator. */
void _resizeHashTable(struct hashTable *ht) {
	int i = 0;
	struct hashTable *newTable = (struct hashTable *) malloc(sizeof(struct hashTable));
	assert(newTable != NULL);
	initHashTable(newTable, 2 * ht>tablesize);
	struct hlink * iter = ht->table[i];
	while (i < ht->tablesize) {
		while (iter != NULL) {
			hashTableAdd(newTable, iter->value);
			hashTableRemove(ht, iter->value);
			iter = iter->next;
		}
		iter = ht->table[i++]
	}
	for (i = 0; i < ht->tablesize; i++) {
		if (ht->table[i] != NULL) {
			free(ht->table[i]);
			ht->table[i] = NULL;
		}
	}
	ht->table = newTable;
	ht->tableSize *= 2;
}


int containsHashTable(struct hashTable *ht, TYPE testElement) {
	int hash = HASH(testElement);
	int hashIndex = (int)(labs(hash) % ht->tablesize); //"labs" = "absolute value of long integer".
	struct hlink *current;
	cur = ht->table[hashIndex];
	while (cur != 0) {
		if (cur->value == testElement)
			return 1;
		current = current->next;
	}
	return 0;
}


void removeHashTable(struct hashTable *ht, TYPE testElement) {
	assert(ht != 0);
	int hash = HASH(testElement);
	int hashIndex = (int)(labs(hash) % ht->tablesize);
	struct hlink *cur, *last;

	if (containsHashTable(ht, testElement)) {
		cur = ht->table[hashIndex];
		last = ht->table[hashIndex];
		while (cur != 0) {
			if (cur->value == testElement) {
				if (cur == ht->table[hashIndex]) // Special case 1st.
					ht->table[hashIndex] = cur->next;
				else
					last->next = cur->next;
				free(cur);
				cur = 0; // To enable loop exit.
			}
			else {
				last = cur;
				cur = cur->next;
			}
		}
	}ht->count--;
}