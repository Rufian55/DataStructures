/* CS261- Assignment 1 - Q. 0 */
/* Name: Chris Kearns
 * Date: 10 April 2016
 * Solution description: Pointer manipulation Demo in C.
 */
 
#include <stdio.h>
#include <stdlib.h>


void fooA(int* iptr){
	/*Print the value pointed to by iptr*/
	printf("From fooA(): Value pointed to by iptr = %d\n", *iptr);

	/*Print the address pointed to by iptr*/
	printf("From fooA(): Memory adress pointed to by iptr = %p\n", iptr);

	/*Print the address of iptr itself*/
	printf("From fooA(): Memory address of iptr itself = %p\n", (void*)&iptr); // [1] [3]
}


int main(){
	/*declare an integer x*/
	int x = 261;

	/*print the address of x*/
	printf("From main(): Address of x = %p\n", (void*)&x); // [2] [3]
 
	/*Call fooA() with the address of x*/
	fooA(&x);

	/*print the value of x*/
	printf("From main(): Value of x = %i\n", x);

	return 0;
}
/*
[Citations]
[1] Cast method found at http://stackoverflow.com/questions/30183499/printing-address-a-pointer-points-to-value-the-address-points-to-and-the-addre
[2] Cast method found at http://stackoverflow.com/questions/5286451/how-to-print-variable-addresses-in-c
[3] Line 18 and Line 26 work without '(void*)', however, when compiled with -pedantic errors flag on, gcc will issue a warning.
*/