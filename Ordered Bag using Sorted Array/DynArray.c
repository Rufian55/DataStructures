#include "DynArray.h"

void initDynArr(struct DynArr *v, int capacity) {
	v->data = malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);

	v->size = 0;
	v->capacity = capacity;
}

void freeDynArr(struct DynArr *v) {
	if (v->data != 0) {
		free(v->data);
		v->data = 0;
	}
	v->size = 0;
	v->capacity = 0;
}

int sizeDynArr(struct DynArr *v){
	return v->size;
}

void addDynArr(struct DynArr *v, TYPE val){
	if (v->size >= v->capacity)
		_setCapacityDynArr(v, 2 * v->capacity);
	v->data[v->size] = val;
	v->size++;
}

void _setCapacityDynArr(struct DynArr *v, int newCap){
	TYPE *newData;
	int count;
	newData = malloc(sizeof(TYPE) * newCap);
	for (count = 0; count < v->capacity; ++count)
		newData[count] = v->data[count];
	free(v->data);
	v->data = newData;
	v->capacity = newCap;
}

TYPE getDynArr(struct DynArr * da, int position) {
	assert(position < da->size && position >= 0);
	return da->data[position];
}

void putDynArr(struct DynArr * da, int position, TYPE value) {
	assert(position < da->size && position >= 0);
	da->data[position] = value;
}

void swapDynArr(struct DynArr * da, int i, int j) {
	assert(i < da->size && i >= 0);
	assert(j < da->size && j >= 0);
	TYPE tempData = da->data[i];
	putDynArr(da, i, da->data[j]);
	putDynArr(da, j, tempData);
}

void removeAtDynArr(struct DynArr * da, int index) {
	assert(index < da->size && index >= 0);
	int count;
	for (count = index; count < da->size - 1; ++count)
		da->data[count] = da->data[count + 1];
	da->size--;
}

/* O(log n) standard binary search algorithm for an array.
 returns, in O(log n) steps, either the location at which
 the value is found, or if it is not in the collection the
 location the value can be inserted and still preserve order.*/
int binarySearch(TYPE * data, int size, TYPE testValue) {
	int low = 0;
	int high = size;
	int mid;
	while (low < high) {
		mid = ((unsigned int)low + (unsigned int)high) >> 1;
		if (LT(data[mid], testValue))
			low = mid + 1;
		else
			high = mid;
	}
	return low;
}

/* //Testing main() for Dynamic Array implementatin above.
int main(int argc, const char * argv[]){
	struct DynArr myData;
	initDynArr(&myData, 2);

	addDynArr(&myData, 5);
	addDynArr(&myData, 8);
	addDynArr(&myData, 10);

	swapDynArr(&myData, 1, 2);

	removeAtDynArr(&myData, 2);

	printf("Value 0 stored: %d\n", getDynArr(&myData, 0));
	printf("Value 1 stored: %d\n", getDynArr(&myData, 1));

	freeDynArr(&myData);

	return 0;
}
 */