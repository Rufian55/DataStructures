/**************************************************************************
** dynamicArray.c: 
** Dynamic Array implementation.
** Author: Chris Kearns
** Implementation of stack and bag with an unerlying dynamic array.
** Requires #inlcude dynArray.h and is tested with testDynArray.c
**************************************************************************/
#include <assert.h>
#include <stdlib.h>
#include "dynArray.h"

struct DynArr {
	TYPE *data;	/* pointer to the data array */
	int size;	/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};


/*************************************************************************
			Dynamic Array Functions
**************************************************************************/

/* Initialize (including allocation of data array) dynamic array.
	param: 	v = pointer to the dynamic array
	param:	cap = capacity of the dynamic array
	pre:		v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
*/
void initDynArr(DynArr *v, int capacity) {
	assert(capacity > 0);
	assert(v!= 0);
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;	
}


/* Allocate and initialize dynamic array.
	param:	cap = desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
		and 0 elements in it.		
*/
DynArr* newDynArr(int cap) {
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}


/* Deallocate data array in dynamic array. 
	param: 	v = pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v) {
	if(v->data != 0) {
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}


/* Deallocate data array and the dynamic array pointer. 
	param: 	v = pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v) {
	freeDynArr(v);
	free(v);
}


/* Resizes the underlying array to be the size existing
   capacity * newCap parameter (e.g. cap * newCap where 
   newCap = 2 would double the array capacity.
	param:	v = pointer to the dynamic array
	param:	cap = the new desired capacity
	pre:	v is not null
	post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap) {	
	int theNewCap = newCap * v->capacity;
	TYPE *newArr;
	newArr = malloc((sizeof(TYPE) * theNewCap));

	/* Transfer values from old array to new array */
	int count;
	for (count = 0; count < v->capacity; ++count)
		newArr[count] = v->data[count];

	/* Free old array memory */
	free(v->data);

	/* Reassign pointer to point to newData address */
	v->data = newArr;
	/* Update new capacity */
	v->capacity = theNewCap;
}


/* Get the size of the dynamic array
	param:	v = pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v){
	return v->size;
}


/* Get the capacity of the dynamic array
param:	v = pointer to the dynamic array
pre:	v is not null
post:	none
ret:	the capacity of the dynamic array
*/
int capDynArr(DynArr *v) {
	return v->capacity;
}


/* Adds an element to the end of the dynamic array
	param: 	v = pointer to the dynamic array
	param:	val = the value to add to the end of the dynamic array
	pre:	the dynArry is not null
	post:	size increases by 1
	post:	if reached capacity, capacity is increased by a factor
		of the the second parameter of the _dynArrSetCapacity()
		call.
	post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val) {
	/* Check to see if a resize is necessary */
	if (v->size == v->capacity)
		_dynArrSetCapacity(v, 2);

	v->data[v->size] = val;
	v->size++;
}

/* Get an element from the dynamic array from a specified position
	param:	v = pointer to the dynamic array
	param:	pos = integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
*/
TYPE getDynArr(DynArr *v, int pos){
	/* Ensure that the index position is valid */
	assert(pos <= v->size && pos >= 0);

	/* Return value at position */
	return v->data[pos];
}

/* Put an item into the dynamic array at the specified location,
	overwriting the element that was there
	param:	v = pointer to the dynamic array
	param:	pos = the index to put the value into
	param:	val = the value to insert 
	pre:	v is not null
	pre:	v is not empty
	pre:	pos >= 0 and pos < size of the array
	post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val){
	/* Ensure that the index position is valid */
	assert(pos < v->size && pos >= 0);

	/* insert value */
	v->data[pos] = val;
}

/* Swap two specified elements in the dynamic array
	param: 	v = pointer to the dynamic array
	param:	i,j are the position elements to be swapped
	pre:	v is not null
	pre:	v is not empty
	pre:	i, j >= 0 and i,j < size of the dynamic array
	post:	index i now holds the value at j and index j
		now holds the value at i
*/
void swapDynArr(DynArr *v, int i, int  j){
	/* Ensure that the positions are valid */
	assert(i < v->size && i >= 0);
	assert(j < v->size && j >= 0);

	/* Swap the values */
	TYPE tempData = v->data[i];
	putDynArr(v, i, v->data[j]);
	putDynArr(v, j, tempData);
}

/* Remove the element at the specified location from the array,
   shifts other elements back one to fill the gap
	param:	v = pointer to the dynamic array
	param:	idx = location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *v, int idx){
	/* Ensure that the position is valid */
	assert(idx < v->size && idx >= 0);

	/* Bring all the values past that point back one */
	for (int count = idx; count < v->size - 1; ++count)
		v->data[count] = v->data[count + 1];

	/* Decrement size */
	v->size--;
}


/*************************************************************************
			Stack Interface Functions
**************************************************************************/

/* Returns boolean (encoded as an int) demonstrating whether or not the 
   dynamic array stack has an item on it.
   	param:	v = pointer to the dynamic array
	pre:	the dynArr is not null
	post:	none
	ret:	1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *v){
	if (sizeDynArr(v) == 0)
		return 1;
	else
		return 0;
}

/* Push an element onto the top of the stack
	param:	v = pointer to the dynamic array
	param:	val = the value to push onto the stack
	pre:	v is not null
	post:	size increases by 1
		if reached capacity, capacity is doubled
		val is on the top of the stack
*/
void pushDynArr(DynArr *v, TYPE val){
	addDynArr(v, val);
}

/* Returns the element at the top of the stack 
	param:	v = pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the stack
*/
TYPE topDynArr(DynArr *v){
	assert(sizeDynArr(v) > 0);
	return getDynArr(v, sizeDynArr(v) -  1);
}

/* Removes the element on top of the stack 
	param:	v = pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	size is decremented by 1
		the top has been removed
*/
void popDynArr(DynArr *v){
	assert(sizeDynArr(v) > 0);
	v->size--;
}

/*************************************************************************
			Bag Interface Functions
**************************************************************************/

/* Returns boolean (encoded as an int) demonstrating whether or not
   the specified value is in the collection
	true = 1
	false = 0
	param:	v = pointer to the dynamic array
	param:	val = the value to look for in the bag
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the bag
*/
int containsDynArr(DynArr *v, TYPE val){
	int i;
	for (i = 0; i < sizeDynArr(v); i++) {
		if (EQ(getDynArr(v, i), val)) {
			return 1;
		}
	}
	return 0;
}

/* Removes the first occurrence of the specified value from the collection
   if it occurs.
   	param:	v = pointer to the dynamic array
	param:	val = the value to remove from the array
	pre:	v is not null
	pre:	v is not empty
	post:	val has been removed
	post:	size of the bag is reduced by 1
*/
void removeDynArr(DynArr *v, TYPE val){
	int i;
	for (i = 0; i < v->size; i++) {
		if (EQ(val, v->data[i])) { /* found it */
			removeAtDynArr(v, i);
			return;
		}
	}
}
