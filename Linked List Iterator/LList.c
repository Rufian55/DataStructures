/**************************************************************************
** LList.c
** Author: Chris Kearns
** A linked list deque implementation
** Compile with gcc -Wall -std=c99 LList.h LList.c -o LList
**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "LList_Iterator.h"

void LinkedListInit(struct linkedList *q){
	q->frontSentinel = malloc(sizeof(struct dlink));
	assert(q->frontSentinel != 0);
	q->backSentinel = malloc(sizeof(struct dlink));
	assert(q->backSentinel);
	q->frontSentinel->next = q->backSentinel;
	q->backSentinel->prev = q->frontSentinel;
	q->size = 0;
}

void LinkedListFree(struct linkedList *q){
	while (q->size > 0)
		LinkedListRemoveFront(q);
	free(q->frontSentinel);
	free(q->backSentinel);
	q->frontSentinel = q->backSentinel = NULL;
}

void LinkedListAddFront(struct linkedList *q, TYPE e) {
	_addBefore(q, q->frontSentinel->next, e);
}

void LinkedListAddBack(struct linkedList *q, TYPE e){
	_addBefore(q, q->backSentinel, e);
}

void LinkedListRemoveFront(struct linkedList *q){
	assert(!LinkedListIsEmpty(q));
	_removeLink(q, q->frontSentinel->next);
}

void LinkedListRemoveBack(struct linkedList *q){
	assert(!LinkedListIsEmpty(q));
	_removeLink(q, q->backSentinel->prev);
}

int LinkedListIsEmpty(struct linkedList *q){
	return q->size == 0;
}

void _addBefore(struct linkedList *q, struct dlink *lnk, TYPE e) {
	/* make a new node */
	struct dlink *newNode = malloc(sizeof(struct dlink));
	assert(newNode != 0);

	/* set pointers and value in the new node */
	newNode->next = lnk;
	newNode->prev = lnk->prev;
	newNode->value = e;

	/* adjust the node pointers before and after the new node */
	newNode->prev->next = newNode;
	newNode->next->prev = newNode;

	/* increment size */
	q->size++;
}

void _removeLink(struct linkedList *q, struct dlink *lnk) {
	assert(!LinkedListIsEmpty(q));

	/* adjust surrounding neighbors to point to each other */
	lnk->next->prev = lnk->prev;
	lnk->prev->next = lnk->next;

	/* free the memory */
	free(lnk);
	lnk = NULL;

	/* decrement size */
	q->size--;
}

TYPE LinkedListFront(struct linkedList *q){
	assert(!LinkedListIsEmpty(q));
	return q->frontSentinel->next->value;
}

TYPE LinkedListBack(struct linkedList *q){
	assert(!LinkedListIsEmpty(q));
	return q->backSentinel->prev->value;
}

/* // Testing main() for the Linked List implementation above.
int main(int argc, char* argv[]) {
	struct linkedList aLList;
	struct linkedList *LL = 0;
	LL = &aLList;
	LinkedListInit(LL);

	printf("Call to LinkedListIsEmpty returns %d\n", LinkedListIsEmpty(LL));
	LinkedListAddBack(LL, 10);
	printf("Call to LinkedListIsEmpty returns %d\n", LinkedListIsEmpty(LL));
	printf("Call to LinkedListFront returns %d\n", LinkedListFront(LL));
	printf("Call to LinkedListBack returns %d\n", LinkedListBack(LL));
	LinkedListAddBack(LL, 20);
	LinkedListAddFront(LL, 5);
	printf("Call to LinkedListFront returns %d\n", LinkedListFront(LL));
	printf("Call to LinkedListBack returns %d\n", LinkedListBack(LL));
	LinkedListRemoveFront(LL);
	printf("Call to LinkedListFront returns %d\n", LinkedListFront(LL));
	LinkedListRemoveBack(LL);
	printf("Call to LinkedListBack returns %d\n", LinkedListBack(LL));
	
	LinkedListFree(LL);
	return 0;
}
*/
