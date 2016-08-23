/* CS261- Assignment 1 - Q.4 */
/* Name: Chris Kearns
 * Date: 10 April 2016
 * Solution description: Demo program in C that instantiates a randomly
 * filled dynamic struct array and performs an ascending order sort on student
 * scores using the selection sort algorithm. 
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>


struct student{
	int id;
	int score;
};

/***************************************************************************************
** Function: sort()
** Description: Sorts the given array of n students based on their score where where
** length n is the number of students using a bubble sort variant algorithm.
** See citation[1]
** Parameters: int pointer to students array and int n, the size of the array argument.
** Pre-Conditions: An int array with at least one ID and score pair value inserted.
** Post-Conditions: students array sorted by score retaining pairing to ID.
****************************************************************************************/
/*Sort . */
void sort(struct student* students, int n){
	int i;
	int j;

	for (i = 1; i < n; i++) {
		for (j = 0; j < n - i; j++) {
			if ( (students + j)->score > (students + j + 1)->score) {
				struct student temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}
}


int main(){
	/*Declare an integer n and assign it a value.*/
	int n = 20;

	/*Allocate memory for n students using malloc.*/
	struct student *students = (struct student *)malloc(sizeof(struct student) * n);

	/*Generate random IDs and scores for the n students, using rand().*/
	int i = 0;
	int randomId = -1;
	int *studsID = (int *)malloc(sizeof(int) * (n + 1)); // changed (n + 1) to correct valgrind read error.
	int flag = 0;
	int randomScore = 0;

	/*Initialize studsID array for keeping track of unique ID's issued.*/
	for (i = 0; i < n; i++) {
		studsID[i] = i + 1;
	}

	/* Generate unique ID randonly from 1 to n inclusive.*/
	for (i = 0; i < n; i++) {
		do {
			flag = 0;
			randomId = (rand() % n) + 1;
			randomScore = rand() % 100;
			if (studsID[randomId] != -1) {
				(students + i)->id = randomId;
				studsID[randomId] = -1;
				(students + i)->score = randomScore;
				flag = 1;
			}
		} while (flag == 0);
	}

	/*Print the contents of the array of n students.*/
	for (i = 0; i < n; i++) {
		printf("%3i %i\n", (students + i)->id, (students + i)->score);
	}

	/*Pass this array along with n to the sort() function*/
	sort(students, n);

	printf("\n");

	/*Print the contents of the array of n students.*/
	for (i = 0; i < n; i++) {
		printf("%3i %i\n", (students + i)->id, (students + i)->score);
	}

	/*Clean up malloc allocated memory.*/
	if (studsID != NULL)
		free(studsID);
	if(students != NULL)
		free(students);
	
	return 0;
}

/*
[Citations]
[1] Adapted from Early C Objects, 8th Edition, 2014, Gaddis, pg. 611.
*/