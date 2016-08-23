/* CS261- Assignment 1 - Q.5 */
/* Name: Chris Kearns
 * Date: 10 April 2016
 * Solution description: Demo program for converting c-strings to 
 * alternating uppercase / lowercase in C via ASCII arithmetic.
 */
 
#include <stdio.h>
#include <stdlib.h>


/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}


/* Converts ch to lower case, assuming it is in upper case currently. */
char toLowerCase(char ch){
     return ch-'A'+'a';
}


/***************************************************************************************
** Function: sticky()
** Description: Converts a c-string to alternating upper and lowe case.
** Parameters: char pointer to the string.
** Pre-Conditions: A user input string passed to this function as a char pointer.
** Post-Conditions: A mutated string of alternating upper and lower caps.
****************************************************************************************/
void sticky(char* word){
	/* Get string length. */
	int len = 0;
	while (word[len] != '\0')
		len++;
	/* Convert string. */
	int i;
	for (i = 0; i < len; i++) {
		if (i % 2 == 0) {
			if (word[i] >= 'a' && word[i] <= 'z') {
				word[i] = toUpperCase(word[i]);
			}
		}
		else {
			if (word[i] >= 'A' && word[i] <= 'Z') {
				word[i] = toLowerCase(word[i]);
			}
		}
	}
}


int main(){
    /* Read word from the keyboard using scanf. */
	printf("Enter the string to be converted to alternating upper/lower case!\n"
		"Keep the following in mind!\n"
		"Maximum of 80 characters.\n"
		"Spaces allowed.\n"
		"Most punctuation is accepted but won't be converted.\n");
	char word[80];
	scanf("%80[0-9a-zA-Z `~!@#$%^&*()_+=-;[/]{}|]", word); //see note [1]

    /* Call sticky. */
	sticky(word);

	/* Print the new word. */
	printf("%s\n", word);

    return 0;
}
/*
[Citations and notes]
[1] Line 55 is a regular expression. Allows upto 80 characters input. Between the "[" 
	and "]" are the characters this scanf() will accept, including spaces.
	Q5 specifications are met, single word will alternate upper/lower case.
*/