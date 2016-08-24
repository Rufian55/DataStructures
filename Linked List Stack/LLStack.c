/**************************************************************************
** CS261-400-S16
** Chris Kearns (kearnsc@oregonstate.edu)
** Worksheet 17
** Worksheet17.c: A linked list Stack implementation
** Compile with gcc -Wall -std=c99 Worksheet17.h Worksheet17.c -o WS17
**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Worksheet17.h"


void linkedListStackInit(struct linkedListStack *s) {
	s->firstLink = 0;
}

void linkedListStackFree(struct linkedListStack *s) {
	while (!linkedListStackIsEmpty(s)) {
		linkedListStackPop(s);
	}
}

void linkedListStackPush(struct linkedListStack *s, TYPE d) {
	struct link *newLink = /*(struct link *)*/malloc(sizeof(struct link));
	assert(newLink != 0);
	newLink->value = d;
	newLink->next = s->firstLink;
	s->firstLink = newLink;
}

TYPE	linkedListStackTop(struct linkedListStack *s) {
	assert(!linkedListStackIsEmpty(s));
	return s->firstLink->value;
}

void linkedListStackPop(struct linkedListStack *s) {
	assert(!linkedListStackIsEmpty(s));
	struct link *pop = s->firstLink;
	s->firstLink = pop->next;
	free(pop);
}

int linkedListStackIsEmpty(struct linkedListStack *s) {
	return s->firstLink == 0;
}


int main(int argc, char* argv[]){
	struct linkedListStack realStack;
	struct linkedListStack *stack = 0;
	stack = &realStack;
	linkedListStackInit(stack);

	printf("The stack is empty = %i\n", linkedListStackIsEmpty(stack));
//	printf("Top of empty stack = %i\n", linkedListStackTop(&stack));
	linkedListStackPush(stack, 10);
	printf("Top of stack is now = %i\n", linkedListStackTop(stack));
	printf("The stack is empty = %i\n", linkedListStackIsEmpty(stack));
	linkedListStackPush(stack, 20);
	printf("Top of stack is now = %i\n", linkedListStackTop(stack));
	linkedListStackPush(stack, 30);
	printf("Top of stack is now = %i\n", linkedListStackTop(stack));
	linkedListStackPush(stack, 40);
	printf("Top of stack is now = %i\n", linkedListStackTop(stack));
	linkedListStackPush(stack, 50);
	printf("Top of stack is now = %i\n", linkedListStackTop(stack));

	linkedListStackPop(stack);
	printf("Top of stack is now = %i\n", linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Top of stack is now = %i\n", linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Top of stack is now = %i\n", linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Top of stack is now = %i\n", linkedListStackTop(stack));
	linkedListStackPop(stack);
//	printf("Top of stack is now = %i\n", linkedListStackTop(stack));
	printf("The stack is empty = %i\n", linkedListStackIsEmpty(stack));

	linkedListStackFree(stack);
	return 0;
}