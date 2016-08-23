/**************************************************************************************
** Program Filename:	Convertor.c				Date:  31 March 2016
** Author: Chris Kearns	Course: CS261-400_Spring_2016	email: kearnsc@oregonstate.edu
** Description: A short demo program in C that prompts user for an inch or cm value
** and converts it from inches to cm or vice versa. Includes input validation.
** Inputs: User prompted.
** Outputs: printf() to console only.
**************************************************************************************/
#include <stdio.h>
#define CM2IN 0.39370079
#define IN2CM 2.54

int main(int argc, char **argv) {
	int input = 0;			// Our initial user input prompt collection var.
	double inchInput = 0;	// Local user input collection var.
	double cm;			// Our resulting cm var.
	double cmInput = 0;		// Local user input collection var.
	double inch;			// Our resulting inch var.

	do {
		// Determine which conversion user wants to perform.
		printf("Which Unit would you like to convert?\n"
			"Press 1 for inches to centimters.\n"
			"Press 2 for centimeters to inches\n"
			"Press any other integer to quit.\n");
		scanf("%d", &input);

		// Prompt user for selected conversion var, process and display result.
		if (input == 1) {
			printf("Enter your inch value to be converted to cm!\n");
			if (scanf("%lf", &inchInput) != 1) { printf("Input error!\n"); break; }
			cm = inchInput * IN2CM;
			printf("%.3lf inches converts to %.3lf centimeters.\n", inchInput, cm);
		}
		else if (input == 2) {
			printf("Enter your cm value to be converted to inches!\n");
			if (scanf("%lf", &cmInput) != 1) { printf("Input error!\n"); break; }
			inch = cmInput * CM2IN;
			printf("%.4lf cm converts to %.4lf inches.\n", cmInput, inch);
		}
		else {
			printf("Thank you for using Convertor.c by Chris!\n");
			break;
		}
	} while (input == 1 || input == 2);

	return 0;
}