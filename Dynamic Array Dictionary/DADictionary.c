#include "DADictionary.h"

/* Finds and places the value associated with key in valptr */
void dyArrayDictionaryGet(struct DynamicArray *da, KEYTYPE key, VALUETYPE *valptr) {
	struct association *ap;
	int i;
	for (i = 0; i < da->size; i++) {
		ap = da->data[i];
		if ((compareFunction)(key, ap->key) == 0) {
			valptr = ap->value;
		}
	}
}


void dyArrayDictionaryPut(struct DynnamicArray *da, KEYTYPE key, VALUETYPE val) {
	struct association *ap;
	if (dyArrayDictionaryContainsKey(da, key))
		dyArrayDictionaryRemove(da, key);
	ap = (struct association *) malloc(sizeof(struct association));
	assert(ap != 0);
	ap->key = key;
	ap->value = val;
	dyAdd(da, ap);
}


int dyArrayDictionaryContainsKey(struct DynamicArray *da, KEYTYPE key) {
	struct association *ap;
	int i;
	for (i = 0; i < da->size; i++) {
		ap = da->data[i];
		if ((compareFunction)(key, ap->key) == 0) {
			return 1;
		}
		return 0;
	}
}


void dyArrayDictionaryRemove(struct DynamicArray *da, KEYTYPE key) {
	int i;
	struct association * ap;
	for (i = 0; i < da->size; i++) {
		ap = (struct association *)da->data[i];
		if ((compareFunction)(key, ap->key) == 0){
			dyRemoveAt(da, i);
			free(ap);
		}
	}
}