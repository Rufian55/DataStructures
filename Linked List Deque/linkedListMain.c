/**************************************************************************
 * linkedListMain.c
 * Author: Chris Kearns
 * Date: 26 Apr 2016
 * Testing main for linked list implementation file linkedList.c and a 
 * memory usage testing battery for determining miliseconds to execute
 * via a command line call to the compiled executable.
 *************************************************************************/
#include "linkedList.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* COMMENT OUT THE LINE BELOW TO EXCLUDE THE MEMORY TEST CODE. */
#define MEMORY_TEST_INCLUDED

#ifdef MEMORY_TEST_INCLUDED
// This header is needed for memory usage calculation.
#include <sys/resource.h> 

// Function to get current memory usage in KB (Max Resident Set Size)
long getMemoryUsage() {
	int who = RUSAGE_SELF; 
	struct rusage usage; 
	getrusage(who, &usage);	
	return usage.ru_maxrss;
}
#endif

// Function to get number of milliseconds elapsed since program started execution
double getMilliseconds(){
	return 1000.0 * clock() / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]){
	if (argc != 2) {
		printf("Usage: %s <number of elements to add>\n", argv[0]);
		return 1;
	}

	struct LinkedList* list = linkedListCreate();
	int numElements = atoi(argv[1]);

	for (int i = 0; i < numElements; i++) {
		linkedListAdd(list, (TYPE)i);
	}

	#ifdef MEMORY_TEST_INCLUDED
	// Memory used BEFORE creating LinkedList
	long m1 = getMemoryUsage();
	#endif

	#ifdef MEMORY_TEST_INCLUDED
	// Memory used AFTER creating LinkedList
	long m2 = getMemoryUsage();
	printf("Memory used by LinkedList: %ld KB \n", m2 - m1);
	#endif

	double t1 = getMilliseconds(); // Time before contains()
	for (int i = 0; i < numElements; i++) {
		linkedListContains(list, i);
	}
	double t2 = getMilliseconds(); // Time after contains()
	printf("Time for running contains() on %d elements: %g ms\n", numElements, t2 - t1);

	linkedListDestroy(list);

	return 0;
/*
	// Validating our linkedList implementation TEST BATTERY:
	struct LinkedList* list = linkedListCreate();

	linkedListAddBack(list, 99);
	linkedListAddFront(list, 69);
	linkedListAddFront(list, 98);
	linkedListAddBack(list, 100);
	linkedListAddFront(list, 97);

	linkedListPrint(list);
	printf("LLback = %d\n", linkedListBack(list));
	printf("LLfront = %d\n", linkedListFront(list));

	printf("contains 69 = %d\n", linkedListContains(list, 69));
	linkedListRemove(list, 69);
	printf("contains 69 = %d\n", linkedListContains(list, 69));

	linkedListPrint(list);

	linkedListRemoveBack(list);
	linkedListPrint(list);

	linkedListRemoveFront(list);
	linkedListPrint(list);
	printf("LLfront contains: %d\n", linkedListFront(list));
	printf("LLback contains: %d\n", linkedListBack(list));

	linkedListDestroy(list);
	return 0;
*/
}