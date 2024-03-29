/**************************************************************************************
 * dynamicArrayMain.c
 * Date: 23 Aug 2016
 * Author: Chris Kearns
 * An alternate main for dynamic array implementation to test memory usage under 
 * various load.  ./makefile needs to be modified to use this main.
*************************************************************************************/

#include "dynArray.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* VISUAL STUDIO (VS) USERS: COMMENT OUT THE LINE BELOW TO EXCLUDE MEMORY TEST CODE */
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
double getMilliseconds() {
	return 1000.0 * clock() / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]) {
	#ifdef MEMORY_TEST_INCLUDED
	// Memory used BEFORE creating LinkedList
	long m1 = getMemoryUsage();
	#endif

	if (argc != 2) {
		printf("Usage: %s <number of elements to add>\n", argv[0]);
		return 1;
	}
	
	DynArr *a = newDynArr(1024);
	int numElements = atoi(argv[1]);
	for (int i = 0 ; i < numElements; i++){
		addDynArr(a, (TYPE)i);
	}

	#ifdef MEMORY_TEST_INCLUDED
	// Memory used AFTER creating LinkedList
	long m2 = getMemoryUsage();
	printf("Memory used by Dynamic Array: %ld KB \n", m2 - m1);
	#endif

	double t1 = getMilliseconds(); // Time before contains()
	for (int i = 0; i < numElements; i++){
		containsDynArr(a, i);
	}
	double t2 = getMilliseconds(); // Time after contains()
	printf("Time for running contains() on %d elements: %g ms\n", numElements, t2 - t1);

	deleteDynArr(a);

	return 0;
}
