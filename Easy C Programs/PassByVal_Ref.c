/* CS261- Assignment 1 - Q.2 */
/* Name: Chris Kearns
 * Date: 10 April 2016
 * Solution description: Demo of C behaviour for pass by value vs.
 * pass by reference (pointers).
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
	/*Set a to double its original value*/
	*a *= 2;
	/*Set b to half its original value*/
	*b /= 2;
    /*Assign a+b to c*/
	c = *a + *b;
    /*Return c*/
	return c;
}

int main(){
	/*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
	int x = 5;
	int y = 6;
	int z = 7;
	int result;

	/*Print the values of x, y and z*/
	printf("x = %i\ny = %i\nz = %i\n", x, y, z);

	/*Call foo() appropriately, passing x,y,z as parameters*/
	result = foo(&x, &y, z);

	/*Print the value returned by foo*/
	printf("Returned value from foo = %i\n", result);

	/*Print the values of x, y and z again*/
	printf("x = %i\ny = %i\nz = %i\n", x, y, z);

	/*Is the return value different than the value of z?  Why?*/
    return 0;
}
/*
No, z (equal to 7) was passed to foo by value, (which means a copy of z was passed to foo), not
by reference like x and y were done.  As such, the assignment operation at line 17 was performed
on the copy of z, and that was then returned, leaving the original z in main unchanged.
*/