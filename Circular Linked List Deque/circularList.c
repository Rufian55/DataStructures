/*****************************************************************************
** CS261-400-S16	Assignment 3, Part 3	Due: 24 Apr 2016
** Chris Kearns (kearnsc@oregonstate.edu)
** circularList.c
** A circular linked list deque implementation in C and utilized as below.
** Compile:
gcc -g -Wall -std=c99 circularList.h circularList.c circularListMain.c -o prog
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

/* Double link stuct representing the individual nodes of
the linked list */
struct Link {
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

/* Double linked circular list with one sentinel */
struct CircularList {
	int size;
	struct Link* sentinel;
};

/* Allocates the list's sentinel and sets the size to 0.
	param: 	list = pointer to the LinkedList.
	pre:		Stuct Link defined.
	post:	memory allocated for sentinel Link.
	post:	size var set to zero
	post:	sentinel's next and prev point to sentinel.
*/
static void init(struct CircularList* list){
	list->sentinel = malloc(sizeof(struct Link));
	assert(list->sentinel != 0);
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
	list->size = 0;
}

/* Creates a link with the given value, NULLs next and prev pointers.
	param:	value to be added to new Link.
	pre:		struct Link defined.
	post:	a new Link (unconnected to the list).
	returns:	struct Link pointer to the new Link.
*/
static struct Link* createLink(TYPE value) {
	struct Link* newCLL = malloc(sizeof(struct Link));
	newCLL->next = NULL;
	newCLL->prev = NULL;
	newCLL->value = value;
	return newCLL;
}

/* Adds a new link with the given value after the given link and
   increments the list's size.
	param:	list pointer.
	param:	link pointer (the target link)
	param:	value to be added to the new link.
	pre:		A instantiated list, link, and valid type value.
	post:	New link inserted after target link.
	post:	list size var incremented.
	Note:	target link identified by traversing with next/prev pointers.
*/
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value) {
	struct Link *newLink = createLink(value);
	assert(newLink != 0);
	newLink->prev = link;
	newLink->next = link->next;
	link->next->prev = newLink;
	link->next = newLink;
	list->size++;
}

/* Removes the given link from the list and decrements the list's size.
	param:	list pointer.
	param:	link pointer (the target link)
	pre:		An instantiated non empty list and link.
	post:	link removed.
	post:	list size var decremented.
	Note:	target link identified by traversing with next/prev pointers.
*/
static void removeLink(struct CircularList* list, struct Link* link) {
	assert(!circularListIsEmpty(list));
	link->next->prev = link->prev;
	link->prev->next = link->next;
	free(link);
	link = NULL;
	list->size--;
}

/* Allocates and initializes the circular linked list.
	param:	none.
	pre:		CircularList struct defined.
	post:	see init() function comments.
	returns:	pointer to the circular linked list.
*/
struct CircularList* circularListCreate() {
	struct CircularList* list = malloc(sizeof(struct CircularList));
	assert(list != 0);
	init(list);
	return list;
}

/*Deallocates every link in the list and frees the list pointer.
	param:	CircularList pointer.
	post:	all memeory freed.
	Note:	See circularListRemoveFront comments.
	Note:	See removeLink comments.
*/
void circularListDestroy(struct CircularList* list) {
	struct Link *tmp = list->sentinel;
	if (!circularListIsEmpty(list)) {
		do {
			circularListRemoveFront(list);
			tmp = tmp->next;
		} while (tmp != list->sentinel);
	}
	free(list->sentinel);
	free(list);
	tmp = NULL;
}

/* Adds a new link with the given value to the front of the Circular list.
	param:	CircularList pointer
	param:	value to be added to the new Link.
	post:	new link added to the front of the circular list.
	Note:	See addLinkAfter comments.
	Note:	front defined as immediately after sentinel.
*/
void circularListAddFront(struct CircularList* list, TYPE value){
	addLinkAfter(list, list->sentinel, value);
}

/* Adds a new link with the given value to the back of the Circular list.
param:	CircularList pointer
param:	value to be added to the new Link.
post:	new link added to the back of the circular list.
Note:	See addLinkAfter comments.
Note:	back defined as immediately before sentinel.
*/
void circularListAddBack(struct CircularList* list, TYPE value) {
	addLinkAfter(list, list->sentinel->prev, value);
}

/* Returns the value of the link at the front of the deque.
	param:	list pointer.
	pre:		a non empty list.
	post:	no changes.
	return:	value at front of circular deque.
*/
TYPE circularListFront(struct CircularList* list) {
	assert(!circularListIsEmpty(list));
	return list->sentinel->next->value;
}

/* Returns the value of the link at the back of the deque.
	param:	list pointer.
	pre:		a non empty list.
	post:	no changes.
	return:	value at back of circular deque.
*/
TYPE circularListBack(struct CircularList* list) {
	assert(!circularListIsEmpty(list));
	return list->sentinel->prev->value;
}

/* Removes the link at the front of the deque.
	param:	list pointer.
	pre:		A non empty list - see removeLink().
	post:	front Link is removed.
	Note:	See removeLink comments.
*/
void circularListRemoveFront(struct CircularList* list) {
	removeLink(list, list->sentinel->next);
}

/* Removes the link at the back of the deque.
	param:	list pointer.
	pre:		A non empty list - see removeLink().
	post:	back Link is removed.
	Note:	See removeLink comments.
 */
void circularListRemoveBack(struct CircularList* list) {
	removeLink(list, list->sentinel->prev);
}

/* Returns 1 if the deque is empty and 0 otherwise.
	param:	list pointer.
	note:	EQ defined in circularList.h
	return:	int bool as appropriate.
*/
int circularListIsEmpty(struct CircularList* list) {
	return EQ(list->size, 0);
}

/*Prints the values of the links in the deque from front to back.
	param:	list pointer.
	pre:		a non empty list.
	post:	no changes.
	Note:	LT defined in linkedList.h
 */
void circularListPrint(struct CircularList* list) {
	assert(!circularListIsEmpty(list));
	int i;
	struct Link *tmp = list->sentinel->next;

	for (i = 0; LT(i, list->size); i++) {
		printf("CLL Node %d = %.1f\n", i, tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
	tmp = NULL;
}

/*Reverses the deque.
	param:	list pointer.
	pre:		a non empty list.
	post:	all Link pointers swapped other than
			sentinel itself.
*/
void circularListReverse(struct CircularList* list) {
	assert(!circularListIsEmpty(list));
	struct Link *current = list->sentinel;
	struct Link *next;
	struct Link *temp;

	do{
		next = current->next;
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = next;
	} while (current != list->sentinel);

	current = next = temp = NULL;
}