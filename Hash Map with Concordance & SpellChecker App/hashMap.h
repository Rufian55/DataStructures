#ifndef HASH_MAP_H
#define HASH_MAP_H

#define HASH_FUNCTION hashFunction1
#define MAX_TABLE_LOAD .75

typedef struct HashMap HashMap;
typedef struct HashLink HashLink;

struct HashLink {
    char* key;
    int value;
    HashLink* next;
};

struct HashMap {
    HashLink** table;	// An array of pointers to HashLinks.
    int size;			// Number of links in the table.
    int capacity;		// Number of buckets in the table.
};

HashMap* hashMapNew(int capacity);
void hashMapDelete(HashMap* map);
int* hashMapGet(HashMap* map, const char* key);
void hashMapPut(HashMap* map, const char* key, int value);
void hashMapRemove(HashMap* map, const char* key);
int hashMapContainsKey(HashMap* map, const char* key);

int hashMapSize(HashMap* map);
int hashMapCapacity(HashMap* map);
int hashMapEmptyBuckets(HashMap* map);
float hashMapTableLoad(HashMap* map);
void hashMapPrint(HashMap* map);

#endif
