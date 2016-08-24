/* Dynamic array dictionary interface file */
# ifndef DADICTIONARY
# define DADICTIONARY
# include "dynamicArray.h"

# define TYPE struct association *

# ifndef KEYTYPE
# define KEYTYPE char *
# endif

# ifndef VALUETYPE
# define VALUETYPE double
# endif

struct DynamicArray {
	TYPE* data;
	int size;
	int capacity;
};

struct association {
	KEYTYPE key;
	VALUETYPE value;
};

/* Dictionary */

void dyArrayDictionaryGet(struct DynamicArray *da, KEYTYPE key, VALUETYPE *valptr);

void dyArrayDictionaryPut(struct DynamicArray * da, KEYTYPE key, VALUETYPE val);

int dyArrayDictionaryContainsKey(struct DynamicArray * da, KEYTYPE key);

void dyArrayDictionaryRemoveKey(struct DynamicArray * da, KEYTYPE key);

# endif