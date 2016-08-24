/* Tasks, for Heap Based Priority Queue
 * Name: Chris Kearns 
 * Date: 22 May 2016
 */

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return  The new task.
 */
Task* taskNew(int priority, char* name) {
	Task* tasker = malloc(sizeof(Task));
	tasker->priority = priority;
	sprintf(tasker->name, name);
	return tasker;
}

/**
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task) {
	free(task);
}

/* Casts left and right to Task pointers and returns:
	-1 if left's priority < right's priority,
	 1 if left's priority > right's priority,
	 0 if left's priority == right's priority.
 param left:		Task pointer.
 param right:	Task pointer.
*/
int taskCompare(void* left, void* right) {
	Task* lft = (Task*)left;
	Task* rght = (Task*)right;

	if (lft->priority < rght->priority)
		return -1;
	if (lft->priority > rght->priority)
		return 1;
	return 0;
}

/**
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value) {
	Task* task = (Task*)value;
	printf("(%d, %s)", task->priority, task->name);
}