/* hashMap.c
 * Author: Chris Kearns
 * Date: 29 May 2016
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int hashFunction1(const char* key) {
	int r = 0;
	int i;
	for (i = 0; key[i] != '\0'; i++) {
		r += key[i];
	}
	return r;
}

int hashFunction2(const char* key) {
	int r = 0;
	int i;
	for (i = 0; key[i] != '\0'; i++) {
		r += (i + 1) * key[i];
	}
	return r;
}

/*
 * Creates a new hash table link with a copy of the key string.
 * @param key:		Key string to copy in the link.
 * @param value:	Value to set in the link.
 * @param next:	Pointer to set as the link's next.
 * @return:		Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next) {
	HashLink* link = malloc(sizeof(HashLink));
	link->key = malloc(sizeof(char) * (strlen(key) + 1));
	strcpy(link->key, key);
	link->value = value;
	link->next = next;
	return link;
}

/*
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link: The link to be deleted.
 */
static void hashLinkDelete(HashLink* link) {
	free(link->key);
	free(link);
}

/*
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map:		Our Hashmap.
 * @param capacity:	The number of table buckets in the map.
 */
void hashMapInit(HashMap* map, int capacity) {
	map->capacity = capacity;
	map->size = 0;
	map->table = malloc(sizeof(HashLink*) * capacity);
	int i;
	for (i = 0; i < capacity; i++) {
		map->table[i] = NULL;
	}
}

/*
 * Removes all links in the map and frees all allocated memory. Uses
 * hashLinkDelete to free the links.
 * @param map: The map to be cleaned.
 */
void hashMapCleanUp(HashMap* map) {
	int i;
	HashLink *cur;
	HashLink *nxt;

	for (i = 0; i < hashMapCapacity(map); i++) {
		cur = map->table[i];
		if (cur != NULL)
			nxt = cur->next;
		while (cur != NULL) {
			hashLinkDelete(cur);
			map->size--;
			cur = nxt;
			if (cur != NULL)
				nxt = cur->next;
		}
	}
	free(map->table);
}


/*
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity:	The number of buckets.
 * @return:		The allocated map.
 */
HashMap* hashMapNew(int capacity) {
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/*
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map:	The Hashmap to be deleted.
 */
void hashMapDelete(HashMap* map) {
	hashMapCleanUp(map);
	free(map);
}

/*
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.  Uses HASH_FUNCTION(key) and
 * searchs the entire list to the map's capacity to find the index of the
 * correct linked list bucket. 
 * @param map:	The map to be searched.
 * @param key:	The key to be searched for.
 * @return:	Link value or NULL if no matching link found.
 */
int* hashMapGet(HashMap* map, const char* key) {
	int hash = HASH_FUNCTION(key);
	hash = (int)(labs(hash) % hashMapCapacity(map));
	// Access the map at that index/list node, and return the value. 
	if (map->table[hash] != NULL) {
		HashLink *cur = map->table[hash];
		while (cur != NULL) {
			if (strcmp(cur->key, key) == 0) {
				return &(cur->value);
			}
			else
				cur = cur->next;
		}
	}
	return NULL;
}


/*
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links are 
 * rehashed into it because the capacity has changed.  Old table and
 * any old links are deleted.
 * @param map:		The map to be resized.
 * @param capacity:	The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity) {
	int i = 0;
	HashMap *newMap = hashMapNew(capacity);
	HashLink *cur;

	while (i < hashMapCapacity(map)) {
		cur = map->table[i];
		while (cur != NULL) {
			hashMapPut(newMap, cur->key, cur->value);
			cur = cur->next;
		}
		i++;
	}
	hashMapCleanUp(map);
	map->table = newMap->table;
	map->capacity = capacity;
	map->size = newMap->size;
	free(newMap);
}


/*
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, function just updates the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list.
 * @param map:		The map to be worked on.
 * @param key:		The key to be checked for and potentially added.
 * @param value:	The value to be updated or added.
 */
void hashMapPut(HashMap* map, const char* key, int value) {
	if (hashMapContainsKey(map, key) == 1) {
		*(hashMapGet(map, key)) = value;
	}
	else {
		int hash = HASH_FUNCTION(key);
		hash = (int)(labs(hash) % hashMapCapacity(map));
		map->table[hash] = hashLinkNew(key, value, map->table[hash]);
		map->size++;
		if (hashMapTableLoad(map) >= MAX_TABLE_LOAD) {
			resizeTable(map, (hashMapCapacity(map) * 2));
		}
	}
}


/*
 * Removes and frees the link with the given key from the table. If no such link
 * exists, does nothing. Searches the entire linked list at the given
 * bucket, and if found, uses hashLinkDelete to free the link.
 * @param map:	The map to be worked on.
 * @param key:	The key to be searched for and removed.
 */
void hashMapRemove(HashMap* map, const char* key) {
	int hash = HASH_FUNCTION(key);
	hash = (int)(labs(hash) % hashMapCapacity(map));
	HashLink *cur = map->table[hash];
	HashLink *prev;
	while (cur != NULL) {
		if (strcmp(cur->key, key) == 0) {
			if(cur == map->table[hash])
				map->table[hash] = cur->next;
			else
				prev->next = cur->next;
			hashLinkDelete(cur);
			map->size--;
			return;
		}
		else {
			prev = cur;
			cur = cur->next;
		}
	}
}


/*
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * Uses HASH_FUNCTION(key) and the map's capacity to search the entire list
 * to find the correct index of the linked list bucket.
 * @param map:	The map to be worked on.
 * @param key:	The key to be searched for.
 * @return:	1 if key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key) {
	int hash = HASH_FUNCTION(key);
	hash = (int)(labs(hash) % hashMapCapacity(map));

	HashLink *cur = map->table[hash];
	if (map->table[hash] == NULL) {
		return 0;
	}
	else {
		while (cur != NULL) {
			if (strcmp(cur->key, key) == 0) {
				return 1;
			}
			cur = cur->next;
		}
		return 0;
	}
}

/*
 * Returns the number of links in the table.
 * @param map:	The map to be worked on.
 * @return:	Number of links in the table.
 */
int hashMapSize(HashMap* map) {
	return map->size;
}

/*
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map) {
    return map->capacity;
}

/*
 * Returns the number of table buckets without any links.
 * @param map:	The mpa to be worked on.
 * @return:	Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map) {
	int numEmpties = 0;
	int i;
	for (i = 0; i < hashMapCapacity(map); i++) {
		if (map->table[i] == NULL)
			numEmpties++;
	}
	return numEmpties;
}

/*
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Buckets are linked lists, so this ratio reveals nothing about the number
 * of empty buckets. Size and capacity are cast to float to avoid integer division.
 * @param map:	The map to be worked on.
 * @return:	Table load.
 */
float hashMapTableLoad(HashMap* map) {
	return (float)(hashMapSize(map)) / (float)(hashMapCapacity(map));
}

/*
 * Prints all the links in each of the buckets in the table.
 * @param map:	The map to be printed.
 */
void hashMapPrint(HashMap* map) {
	int i;
	for (i = 0; i < map->capacity; i++) {
		HashLink* link = map->table[i];
		if (link != NULL) {
			printf("\nBucket %i ->", i);
			while (link != NULL) {
				printf(" (%s, %d) ->", link->key, link->value);
				link = link->next;
			}
		}
	}
	printf("\n");
}
