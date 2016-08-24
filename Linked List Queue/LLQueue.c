/**************************************************************************
** LLQueue.c
** Author: Chris Kearns
** A linked list Queue implementation in C.
** Compile with gcc -Wall -std=c99 LLQueue.h LLQueue.c -o WS18
**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "LLQueue.h"


void listQueueInit(struct listQueue *q) {
	struct link *lnk = (struct link *)malloc(sizeof(struct link));
	assert(lnk != 0); /* lnk is the sentinal*/
	lnk->next = 0;
	q->firstLink = q->lastLink = lnk;
}

void listQueueFree(struct listQueue *q) {
	while (!listQueueIsEmpty(q)) {
		listQueueRemoveFront(q);
	}
	free(q->firstLink);
	q->firstLink = q->lastLink = NULL;
}

void listQueueAddBack(struct listQueue *q, TYPE e){
	/* allocate a new link */
	struct link *newLnk = (struct link *)malloc(sizeof(struct link));
	assert(newLnk != 0);
	/* newLnk is at the back, so we set it to 0. */
	newLnk->next = 0;			
	newLnk->value = e;
	/* point the current lastlink->next to the newLnk. */
	q->lastLink->next = newLnk;
	/* reassign lastlink to point at the newLnk at the back. */
	q->lastLink = newLnk;
}

TYPE listQueueFront(struct listQueue *q){
	assert(!listQueueIsEmpty(q));
	/* We look past the sentinal to the front lnk. */
	return q->firstLink->next->value;
}

void listQueueRemoveFront(struct listQueue *q){
	assert(!listQueueIsEmpty(q));
	/* Allocate a temp link & assign the link to be 
	   removed to the temp link. */
	struct link *temp = q->firstLink->next;
	/* repoint firstlink to temps next link */
	q->firstLink->next = temp->next;
	/* delete temp */
	free(temp);
}

int listQueueIsEmpty(struct listQueue *q){
	return q->firstLink->next == 0;
}


int main(int argc, char* argv[]){
	struct listQueue realQueue;
	struct listQueue *queue = 0;
	queue = &realQueue;
	listQueueInit(queue);
	printf("Is queue empty? returns %d\n", listQueueIsEmpty(queue));
	listQueueAddBack(queue, 10);
	printf("listQueueIsEmpty returns %d\n", listQueueIsEmpty(queue));

	printf("listQueueFront returns %d\n", listQueueFront(queue));
	listQueueAddBack(queue, 20);
	printf("listQueueFront returns %d\n", listQueueFront(queue));
	listQueueAddBack(queue, 30);

	printf("listQueueFront returns %d\n", listQueueFront(queue));
	listQueueRemoveFront(queue);
	printf("listQueueFront returns %d\n", listQueueFront(queue));
	listQueueRemoveFront(queue);
	printf("listQueueFront returns %d\n", listQueueFront(queue));
	listQueueRemoveFront(queue);
//	printf("listQueueFront returns %d\n", listQueueFront(queue));

	printf("Is queue empty? returns %d\n", listQueueIsEmpty(queue));


	listQueueFree(queue);
	return 0;
}