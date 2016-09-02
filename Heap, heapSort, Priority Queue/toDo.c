/* Heap Based Priority Todo list.
 * Name: Chris Kearns
 * Date: 22 May 2016
 */
#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted as:
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file) {
	const int FORMAT_LENGTH = 256;
	char format[FORMAT_LENGTH];
	snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);

	Task temp;
	while (fscanf(file, format, &temp.priority, &temp.name) == 2) {
		dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
	}
}

/**
 * Writes to a file all tasks in heap with lines formatted as:
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file) {
	int i;
	for (i = 0; i < dySize(heap); i++) {
		Task* task = dyGet(heap, i);
	fprintf(file, "%d, %s\n", task->priority, task->name);
	}
}

/**
 * Prints every task in the heap.
 * @param heap
 */
void listPrint(DynamicArray* heap) {
	DynamicArray* temp = dyNew(1);
	dyCopy(heap, temp);
	while (dySize(temp) > 0) {
		Task* task = dyHeapGetMin(temp);
		printf("\n");
		taskPrint(task);
		printf("\n");
		dyHeapRemoveMin(temp, taskCompare);
	}
	dyDelete(temp);
}


/* Handles the given command.
	param:	list - the heap
	param:	command - the user entered input char.
*/
void handleCommand(DynamicArray* list, char command) {
	// Load to-do list from a file.
	if (command == 'l'){
		char path[25] = "./";
		char filename[21];
		printf("Please enter the filename, max 20 characters: ");
		fgets(filename, 20, stdin);
		strcat(path, filename);
		strtok(path, "\n"); // See citation [1]

		FILE * input_file;
		input_file = fopen(path, "r");
		if (input_file == NULL)
			perror("Error");
		else {/* Remove existing tasks and manage memory first. */
			while (dySize(list) != 0) {
				Task * first = dyHeapGetMin(list);
				dyHeapRemoveMin(list, taskCompare);
				free(first);
			}
			listLoad(list, input_file);
			fclose(input_file);
			printf("The list has been loaded from your file succesfully.\n");
		}
	}

	// Save to-do list to a file.
	else if (command == 's') {
		char filename[21];
		printf("Please enter the filename, max 20 characters: ");
		fgets(filename, 20, stdin);
		strtok(filename, "\n");

		FILE * output_file = fopen(filename, "w");
		if (output_file == NULL)
			perror("Error");
		else {
			listSave(list, output_file);
			fclose(output_file);
			printf("The list has been saved into the file succesfully.\n");
		}
	}

	// Add a new task.
	else if (command == 'a') {
		char input[21];
		printf("Please enter the task description, max 20 characters: ");
		fgets(input, 20, stdin);
		strtok(input, "\n");
		int priority;
		printf("Please enter the task priority (0-999): ");
		scanf("%d", &priority);
		dyHeapAdd(list, taskNew(priority, input), taskCompare);
		printf("The task %s has been added to your to-do list.\n", input);
		getchar();// Eats newline.
	}

	// Get the first task.
	else if (command == 'g') {
		if (dySize(list) == 0)
			printf("Your to-do list is empty!\n");
		else {
			Task * first = dyHeapGetMin(list);
			printf("Your first task is: %s\n", first->name);
		}
	}

	// Remove the first task.
	else if (command == 'r') {
		if (dySize(list) == 0)
			printf("Your to-do list is empty!\n");
		else {
			Task * first = dyHeapGetMin(list);
			dyHeapRemoveMin(list, taskCompare);
			printf("Your first task %s has been removed from the list.\n", first->name);
			free(first);
		}
	}

	// Print the list.
	else if (command == 'p') {
		if (dySize(list) == 0)
			printf("Your to-do list is empty!\n");
		else
			listPrint(list);
	}

	else if (command == 'e') {
		/* Manage memory on exit. */
		while (dySize(list) != 0) {
			Task * first = dyHeapGetMin(list);
			dyHeapRemoveMin(list, taskCompare);
			free(first);
		}
		printf("Bye!\n");
	}
}

int main() {
	printf("\n\n** TO-DO LIST APPLICATION **\n\n");
	DynamicArray* list = dyNew(8);
	char command = ' ';
	do {
		 printf("Press:\n"
			"'l' to load to-do list from a file\n"
			"'s' to save to-do list to a file\n"
			"'a' to add a new task\n"
			"'g' to get the first task\n"
			"'r' to remove the first task\n"
			"'p' to print the list\n"
			"'e' to exit the program\n"
		);
		command = getchar();
		// Eat newlines
		while (getchar() != '\n') {
			handleCommand(list, command);
		}
	} while (command != 'e');

	dyDelete(list);
	return 0;
}
