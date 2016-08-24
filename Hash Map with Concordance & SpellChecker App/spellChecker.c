#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define red	"\033[1;31m"		/* 0; normal, 1; is bold. */
#define green	"\033[1;32m"
#define blue	"\033[1;34m"
#define magenta  "\033[1;35m"
#define cyan	"\033[1;36m"
#define none	"\033[0m"			/* "Flush" to default. */

/*
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file) {
	int maxLength = 16;
	int length = 0;
	char* word = malloc(sizeof(char) * maxLength);
	while (1) {
		char c = fgetc(file);
		if ((c >= '0' && c <= '9') ||
		    (c >= 'A' && c <= 'Z') ||
		    (c >= 'a' && c <= 'z') ||
			c == '\'') {
			if (length + 1 >= maxLength) {
				maxLength *= 2;
				word = realloc(word, maxLength);
			}
			word[length] = c;
			length++;
		}
		else if (length > 0 || c == EOF) {
		break;
		}
	}
	if (length == 0) {
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}

/*
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map) {
	if (file == NULL)
		perror("Error");
	else {
		int *count;
		while (1) {
			char *word = nextWord(file);
			if (word == NULL)
				break;
			if (hashMapContainsKey(map, word) == 1) {
				count = (hashMapGet(map, word));
				int nd = *count;
				nd++;
				*(hashMapGet(map, word)) = nd;
			}
			else {
				hashMapPut(map, word, 1);
			}
			free(word);
		}
	}
}

/*
 * Converts a mixed case c-string to all lower case.
 * @param char input[]	The c-string to be converted. 
 */
void case2lower(char input[]) {
	int character = 0;
	while (input[character] != '\0') {
		if (input[character] >= 'A' && input[character] <= 'Z') {
			input[character] = input[character] + 32;
		}
		character++;
	}
}

/*
 * Converts a mixd char c-string to alpha only.
 * @param char input[]	The c-string to be converted. See Citation[1]
 */
void stripPunc(char input[]) {
	int i, j;
	for (i = 0; input[i] != '\0'; i++)	{
		while (! ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') || (input[i] == '\0')) ) {
			for (j = i; input[j] != '\0'; ++j) {
				input[j] = input[j + 1];
			}
			input[j] = '\0';
		}
	}
}


/*
 * Accepts string input, strips all non alpha chars, i.e numerals, punctuation, etc.
 * Checks the cleaned word against the dictionary and returns correct message or 
 * offers user opputunity to add it to the dictionary. (Does not write to dictionary.txt
 * though that would be easy enough...)
 * Because dictionary.txt contains 109,584 words.
 *	109,584 / 0.75 = 146,112. Next prime is 146,117.
 *	Dictionary loads slightly (approx 0.2 secs) faster
 *	since the resize operations are eliminated.
 * 
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv) {
	
	HashMap* map = hashMapNew(146117);
    
	FILE* file = fopen("dictionary.txt", "r");
	clock_t timer = clock();
	loadDictionary(file, map);
	timer = clock() - timer;
	printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	fclose(file);
	printf("%sWelcome to spellChecker 2.0\n"
		  "Enter a word to be checked for correct spelling.\n"
		  "Upper case converts to lower case, punctuation is removed.\n"
		  "SpellChecker 2.0 does not handle contractions out of the box, but you will\n"
		  "be offered a chance to enter these and other new words into the dictionary.\n\n%s", green, none);

	char inputBuffer[256];
	char checkAddWord[256];
	int quit = 0;
	while (!quit) {
		printf("%sEnter a word or \"quit\" to quit:%s ", cyan, none);
		scanf("%s", inputBuffer);
		case2lower(inputBuffer);
		stripPunc(inputBuffer);

		if (hashMapContainsKey(map, inputBuffer)) {
			if (strcmp(inputBuffer, "quit") == 0) {
				printf("%sClosing SpellChecker 2.0, thanks!!\n\n%s", magenta, none);
			}
			else {
				printf("%s%s is in the Dictionary!\n\n%s", green, inputBuffer, none);
			}
		}
		else {
			printf("%sError! %s is NOT in the Dictionary!\n\n%s", red, inputBuffer, none);
			printf("%sWould you like to enter %s into the dictionary?\n"
					"Enter 'Y' or 'y' for yes, any other char for no: %s", cyan, inputBuffer, none);
			printf("\n");
			scanf("%s", checkAddWord);
			if ((strcmp(checkAddWord, "Y") == 0) || (strcmp(checkAddWord, "y") == 0)) {
				hashMapPut(map, inputBuffer, 1);
				printf("%s\nSpellChecker 2.0 has entered %s in the dictionary!\n\n%s", green, inputBuffer, none);
				printf("%sWould you like to update your dictionary.txt file?\n"
						"Enter 'Y' or 'y' for yes, any other char for no: %s", cyan, none);
				printf("\n");
				scanf("%s", checkAddWord);
				if ((strcmp(checkAddWord, "Y") == 0) || (strcmp(checkAddWord, "y") == 0)) {
					FILE* file = fopen("dictionary.txt", "a");
					if (file == NULL) {
						perror("Error");
					}
					else {
						strcat(inputBuffer, "\n");
						fputs(inputBuffer, file);
						fclose(file);
						strtok(inputBuffer, "\n");
						printf("%s\nSpellChecker 2.0 has updated %s in dictionary.txt!\n\n%s", green, inputBuffer, none);
					}
				}
			}
		}
		if (strcmp(inputBuffer, "quit") == 0) {
		quit = 1;
		}
	}

	hashMapDelete(map);
	return 0;
}
// Citation[1] Adapted from h ttp://www.programiz.com/c-programming/examples/remove-characters-string (which had an error!)