#include "DynArray.h"

/***************************************************************************************
** Function: initDynArr()
** Description: Initialize a dynamic array structure with given capacity.
** Parameters: struct DynArr * da, int initialCapacity
** Pre-Conditions: An existing struct DynArr object.
** Post-Conditions: Memory allocation and initialization of struct DynArr variables
** size and capacity.
****************************************************************************************/
void initDynArr(struct DynArr * da, int initialCapacity) {
	da->data = malloc((sizeof(TYPE) * initialCapacity));
	assert(da->data != 0);
	da->size = 0;
	da->capacity = initialCapacity;
}

/***************************************************************************************
** Function: _setCapacityDynArr()
** Description: Internal method to double the capacity of the dynamic array.
** Parameters: struct DynArr * da
** Pre-Conditions: An existing struct DynArr object.
** Post-Conditions: A new struct DynArr object initialzed with the old struct DynArr
** objects data variables and pointers reset appropriately for continued use.
****************************************************************************************/
void _setCapacityDynArr(struct DynArr * da) {
	/* Create a new array with double capacity */
	int doubleCap = 2 * da->capacity;
	TYPE *newArr;
	newArr = malloc((sizeof(TYPE) * doubleCap));

	/* Transfer values from old array to new array */
	int count;
	for (count = 0; count < da->capacity + 1; ++count)
		newArr[count] = da->data[count];

	/* Free old array memory */
	free(da->data);

	/* Reassign pointer to point to newData address */
	da->data = newArr;
	/* Update new capacity */
	da->capacity = doubleCap;
}

/***************************************************************************************
** Function: freeDynArr()
** Description: Release dynamically allocated memory for malloc call.
** Parameters: struct DynArr * da
** Pre-Conditions: An existing struct DynArr object.
** Post-Conditions: A freed memory block (checked with Valgrind).
****************************************************************************************/
void freeDynArr(struct DynArr * da) {
	if (da->data != NULL) {
		free(da->data);
		da->data = 0;
	}
	da->size = 0;
	da->capacity = 0;
}


/***************************************************************************************
** Function: sizeDynArr()
** Description: Returns number of elements stored in dynamic array.
** Parameters: struct DynArr * da
** Pre-Conditions: An existing struct DynArr object.
** Post-Conditions: No change.
****************************************************************************************/
TYPE sizeDynArr(struct DynArr * da) {
	return da->size;
}


/***************************************************************************************
** Function: addDynArr()
** Description: Add value at end of dynamic array.
** Parameters: struct DynArr * da, TYPE value to be added.
** Pre-Conditions: An existing struct DynArr object.
** Post-Conditions: struct DynArr array one additional value appended.
****************************************************************************************/
void addDynArr(struct DynArr * da, TYPE e) {
	/* Check to see if a resize is necessary */
	if (da->size == da->capacity)
		_setCapacityDynArr(da);

	da->data[da->size] = e;
	da->size++;
}


/***************************************************************************************
** Function: removeAtDynArr()
** Description: Remove the value stored at position in the dynamic array.
** Parameters: struct DynArr * da, postion of value to be removed.
** Pre-Conditions: An existing struct DynArr object and a known valid position.
** Post-Conditions: struct DynArr array one value removed.
****************************************************************************************/
void removeAtDynArr(struct DynArr * da, int position) {
	/* Ensure that the index position is valid */
	assert(position < da->size && position >= 0);

	/* Reindex all array elements higher than positon by -1. */
	int count;
	for (count = position; count < da->size; ++count)
		da->data[count] = da->data[count + 1];

	/* Decrement size */
	da->size--;
}


/***************************************************************************************
** Function: getDynArr()
** Description: Returns value at a given position.
** Parameters: struct DynArr * da, position of value to be removed.
** Pre-Conditions: An existing struct DynArr object and a known valid position.
** Post-Conditions: struct DynArr array value returned by position.
****************************************************************************************/
TYPE getDynArr(struct DynArr * da, int position) {
	/* Ensure that the index position is valid */
	assert(position <= da->size && position >= 0);

	/* Return value at position */
	return da->data[position];
}


/***************************************************************************************
** Function: putDynArr()
** Description: Inserts element value at given position by overwriting.
** Parameters: struct DynArr * da, int position, Type value to be inserted.
** Pre-Conditions: An existing struct DynArr object, a known valid position, and a value.
** Post-Conditions: struct DynArr array same number of elements, one now different.
****************************************************************************************/
void putDynArr(struct DynArr * da, int position, TYPE value) {
	/* Ensure that the index position is valid */
	assert(position < da->size && position >= 0);

	/* insert value */
	da->data[position] = value;
}


/**************************************************************************************
**                             BAG IMPLEMENTATION                                    **
***************************************************************************************/

/***************************************************************************************
** Function: removeDynArray()
** Description: Remove the first occurence of the value if found in the bag.
** Parameters: struct DynArr * da.
** Pre-Conditions: An existing struct DynArr object with at least one stored value.
** Post-Conditions: The array has one value "removed" and array is resized.
****************************************************************************************/
void removeDynArr(struct DynArr * da, TYPE test) {
	int i;
	for (i = 0; i < da->size; i++) {
		if (EQ(test, da->data[i])) { /* found it */
			removeAtDynArr(da, i);
			return;
		}
	}
}


/***************************************************************************************
** Function: containsDynArry()
** Description: Searches the bag (array) for the value and returns 1 if found, 0 if not.
** Parameters: struct DynArr * da, and TYPE e (the value searched for).
** Pre-Conditions: An existing struct DynArr object with at least one stored value.
** Post-Conditions: No change to the bag array.
****************************************************************************************/
int containsDynArr(struct DynArr * da, TYPE e) {
	int i;
	for (i = 0; i < sizeDynArr(da); i++) {
		if (EQ(getDynArr(da, i), e)) {
			return 1;
		}
	}
	return 0;
}

/* // Testing main() for Dynamic Array Bag implementation above.
int main(int argc, char* argv[]) {
struct DynArr realArray;
struct DynArr *bag = NULL;
bag = &realArray;
initDynArr(bag, 2);

addDynArr(bag, 2);
printf("Bag contains val 2 = %i\n", containsDynArr(bag, 2));
printf("Bag contains val 3 = %i\n", containsDynArr(bag, 3));
addDynArr(bag, 4);
addDynArr(bag, 5);
addDynArr(bag, 6);
removeDynArr(bag, 5);
printf("Bag contains val 5 = %i\n", containsDynArr(bag, 5));
freeDynArr(bag);

return 0;
}
*/
