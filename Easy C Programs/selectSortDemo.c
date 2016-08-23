/* CS261- Assignment 1 - Q.3 */
/* Name: Chris Kearns
 * Date: 10 April 2016
 * Solution description: Demo program in C that instantiates a randomly
 * filled integer array and performs an ascending order sort using the
 * selection sort algorithm.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>


 /***************************************************************************************
 ** Function: sort()
 ** Description: Sorts the given array number of length n using the selection sort
 ** algorithm.
 ** Parameters: int pointer to number array and int n, the size of the array argument.
 ** Pre-Conditions: An int array with at least one ID and score pair value inserted.
 ** Post-Conditions: number array sorted by score retaining pairing to ID.
 ****************************************************************************************/
 void sort(int* number, int n){ // See citation [1]
	int startScan;
	int minIndex;
	int minValue;
	int index;

	for (startScan = 0; startScan < (n - 1); startScan++) {
		minIndex = startScan;
		minValue = number[startScan];
		for (index = startScan + 1; index < n; index++) {
			if (number[index] < minValue) {
				minValue = number[index];
				minIndex = index;
			}
		}
		number[minIndex] = number[startScan];
		number[startScan] = minValue;
	}
}


int main(){
	/*Declare an integer n and assign it a value of 20.*/
	int n = 20;

	/*Allocate memory for an array of n integers using malloc.*/
	int *aPtr;
	aPtr = (int *)malloc(n * sizeof(int));

	/*Fill this array with random numbers, using rand().*/
	int i;
	for (i = 0; i < n; i++) {
		aPtr[i] = rand();
	}

	/*Print the contents of the array.*/
	for (i = 0; i < n; i++) {
		printf("%i\n", aPtr[i]);
	}

	/*Pass this array along with n to the sort() function of part a.*/
	sort(aPtr, n);

	printf("\n");

	/*Print the contents of the array.*/    
	for (i = 0; i < n; i++) {
		printf("%i\n", aPtr[i]);
	}

	if(aPtr != NULL)
		free(aPtr);

	return 0;
}

/*
[Citations]
[1] Adapted from the selection sort algorithm, C++ Early Objects, 8th Edition, Gaddis, 2014, page 611.
*/