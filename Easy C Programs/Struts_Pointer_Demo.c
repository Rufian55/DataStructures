/* CS261- Assignment 1 - Q.1 */
/* Name: Chris Kearns
 * Date: 10 April 2016
 * Solution description: Demo program illustrating manipulating structs
 * with pointers and pointer arithmetic in a dynamic array of structs.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>


struct student{
	int id;
	int score;
};


/***************************************************************************************
** Function: allocate()
** Description: Initialize a dynamic array structure with given capacity and returns a 
** pointer to said memory block.
** Parameters: none.
** Pre-Conditions: a stuct student definition.
** Post-Conditions: Memory allocation for struct student and accesible through the
** returned pointer.
****************************************************************************************/
struct student* allocate() {
	/* See citation [1] for next line.*/
	struct student *studs = (struct student *)malloc(sizeof(struct student) * 10);

	/*return the pointer*/
	return studs;
}

/***************************************************************************************
** Function: generater()
** Description: Initialize a dynamic array structure with given capacity and returns a
** pointer to said memory block.
** Parameters: struct student pointer to a struct declared in main().
** Pre-Conditions: a stuct student definition and a pointer to same.
** Post-Conditions: A fully initialized struct student array with random unique ID's and
** random scores.
****************************************************************************************/
/*Generate random and unique ID and random scores for ten students,
ID being between 1 and 10, scores between 0 and 100 inclusive.*/
void generate(struct student* students) {
	int i = 0;
	int randomId = -1;
	int studsID[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int flag = 0;
	int randomScore = 0;

	for (i = 0; i < 10; i++) {
		do {
			flag = 0;
			randomId = (rand() % 10) + 1;
			randomScore = rand() % 100;
			if (studsID[randomId] != -1) {
				(students + i)->id = randomId;
				studsID[randomId] = -1;
				(students + i)->score = randomScore;
				flag = 1;
			}
		} while (flag == 0);
	}
}


/***************************************************************************************
** Function: output()
** Description: Outputs formatted student scores by ID.
** Parameters: struct student pointer to a struct declared in main().
** Pre-Conditions: A stuct student definition, a pointer to same, and initialized with
** some values.
** Post-Conditions: No changes.
****************************************************************************************/
void output(struct student* students) {
	int i = 0;
	for (i = 0; i < 10; i++) {
		printf("%3i %i\n", (students + i)->id, (students + i)->score);
	}
}


/***************************************************************************************
** Function: summary()
** Description: Compute and print the minimum, maximum and average scores of the ten
** students
** Parameters: struct student pointer to a struct declared in main().
** Pre-Conditions: a stuct student definition and a pointer to same with values.
** Post-Conditions: No changes.
****************************************************************************************/
void summary(struct student* students){
	int i = 0;
	int minScore = 100;
	int maxScore = 0;
	int avgScore = 0;
	for (i = 0; i < 10; i++) {
		if ((students + i)->score > maxScore) {
			maxScore = (students + i)->score;
		}
		if ((students + i)->score < minScore) {
			minScore = (students + i)->score;
		}
		avgScore += ((students + i)->score);
	}
	avgScore /= 10;
	printf("Minimum Score = %i\nMaximum Score = %i\nAverage Score = %i\n", minScore, maxScore, avgScore);
}


/***************************************************************************************
** Function: deallocate()
** Description: Frees malloc call from allocate().
** Parameters: struct student pointer to a struct declared in main().
** Pre-Conditions: a non NULL stuct student.
** Post-Conditions: Valgrind checks good!
****************************************************************************************/
void deallocate(struct student* stud){
	if(stud != NULL)
		free(stud);
}


int main(){
	struct student* stud = NULL;

	/*call allocate*/
	stud = allocate();

	/*call generate*/
	generate(stud);

    /*call output*/
	output(stud);

	/*call summary*/
	summary(stud);

	/*call deallocate*/
	deallocate(stud);

	return 0;
}

/*
[Citations]
[1] Adpated from Programming in C, 4th Edition, Kochan, 2015, pg 386
*/