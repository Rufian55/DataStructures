/**************************************************************************
** Date: 24 Apr 2016
** Author: Chris Kearns
** linkedList.c
** A linked list deque implementation in C and utilized as below.
** Compile:
   gcc -g -Wall -std=c99 linkedList.h linkedList.c linkedListMain.c -o prog
**************************************************************************/
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* Double link stuct representing the individual nodes of 
   the linked list */
struct Link {
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

/* Double linked list with front and back sentinels */
struct LinkedList {
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/* Allocates the list's sentinels and sets the size to 0.
	param: 	list = pointer to the LinkedList.
	pre:	Stuct Link defined.
	post:	memory allocated for front and back sentinel Links
	post:	size var set to zero
	post:	front sentinel's next and prev point to back sentinel.
	post:	back sentinel's next and prev point to front sentinel.
*/
static void init(struct LinkedList* list) {
	list->frontSentinel = malloc(sizeof(struct Link));
	assert(list->frontSentinel != 0);
	list->backSentinel = malloc(sizeof(struct Link));
	assert(list->backSentinel);
	list->frontSentinel->next = list->backSentinel;
	list->frontSentinel->prev = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;
	list->backSentinel->next = list->frontSentinel;
	list->size = 0;
}

/* Adds a new link with the given value before the given link and
   increments the list's size.
	param: 	list = pointer to the LinkedList.
	param:	link: inseret new Link in frot of "link".
	param:	value = the value contained within the new Link.	
	pre:	An initiated list.
	post:	memory allocated for new Link
	post:	size var incremented.
	post:	preceding and post links next and prev point appropriately.
	post:	new Links next and prev point appropriately.
*/
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value) {
	/* make a new node */
	struct Link *newNode = malloc(sizeof(struct Link));
	assert(newNode != 0);

	/* set pointers and value in the new node */
	newNode->next = link;
	newNode->prev = link->prev;
	newNode->value = value;

	/* adjust the node pointers before and after the new node */
	newNode->prev->next = newNode;
	newNode->next->prev = newNode;

	/* increment size */
	list->size++;
}

/* Removes the given link from the list and decrements the list's size.
   Given link identified by traversing list with next/prev pointers.
	param: 	list = pointer to the LinkedList.
	param:	link: insert new Link in frot of "link".
	pre:	An initiated non empty list.
	post:	removed link's memory freed.
	post:	size var decremented.
	post:	preceding and post links next and prev point appropriately.
*/
static void removeLink(struct LinkedList* list, struct Link* link) {
	assert(!linkedListIsEmpty(list));

	/* adjust surrounding neighbors to point to each other */
	link->next->prev = link->prev;
	link->prev->next = link->next;

	/* free the memory */
	free(link);
	link = NULL;

	/* decrement size */
	list->size--;
}

/* Allocates and initializes a list.
	param:	none.
	pre:	LinkedList struct defined.
	post:	see init() function comments.
	returns: pointer to the linked list.
*/
struct LinkedList* linkedListCreate() {
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	assert(newDeque != 0);
	init(newDeque);
	return newDeque;
}

/*Deallocates every link in the list and frees the list pointer.
	param:	LinkedList pointer.
	post:	all memeory freed.
*/
void linkedListDestroy(struct LinkedList* list) {
	while (!linkedListIsEmpty(list)) {
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/* Adds a new link with the given value to the front of the deque.
	param:	LinkedList pointer
	param:	value to be added to the new Link.
	post:	new link added to the front of the deque.
	Note:	See addLinkBefore comments.
*/
void linkedListAddFront(struct LinkedList* list, TYPE value) {
	addLinkBefore(list, list->frontSentinel->next, value);
}

/* Adds a new link with the given value to the back of the deque.
	param:	LinkedList pointer
	param:	value to be added to the new Link.
	post:	new link added to the back of the deque.
	Note:	See addLinkBefore comments.
*/
void linkedListAddBack(struct LinkedList* list, TYPE value) {
	addLinkBefore(list, list->backSentinel, value);
}

/* Returns the value of the link at the front of the deque.
	param:	Linkedlist pointer.
	pre:	A non empty list.
	post:	No changes.
	return:	front Link node value var contents.
*/
TYPE linkedListFront(struct LinkedList* list) {
	assert(!linkedListIsEmpty(list));
	return list->frontSentinel->next->value;
}

/* Returns the value of the link at the back of the deque.
	param:	Linkedlist pointer.
	pre:	A non empty list.
	post:	No changes.
	return:	back Link node value var contents.
*/
TYPE linkedListBack(struct LinkedList* list) {
	assert(!linkedListIsEmpty(list));
	return list->backSentinel->prev->value;
}

/* Removes the link at the front of the deque.
	param:	list pointer.
	pre:	A non empty list.
	Note:	see removeLink() comments.
*/
void linkedListRemoveFront(struct LinkedList* list) {
	/*assert for empty list already in removeLink.*/
	removeLink(list, list->frontSentinel->next);
}

/* Removes the link at the back of the deque.
	param:	list pointer.
	pre:	A non empty list.
	Note:	see removeLink() comments.
*/
void linkedListRemoveBack(struct LinkedList* list) {
	/*assert for empty list already in removeLink.*/
	removeLink(list, list->backSentinel->prev);
}

/*Returns 1 if the deque is empty and 0 otherwise.
	param:	list pointer.
	Note:	EQ defined in linkedList.h
*/
int linkedListIsEmpty(struct LinkedList* list) {
	return EQ(list->size, 0);
}

/* Prints the values of the links in the deque from
   front to back.
	param:	list pointer.
	pre:	a non empty list.
	post:	no changes.
	Note:	LT defined in linkedList.h
*/
void linkedListPrint(struct LinkedList* list) {
	assert(!linkedListIsEmpty(list));
	int i;
	struct Link *temp;
	temp = list->frontSentinel->next;
	for (i = 0; LT(i, list->size); i++) {
		printf("Node %d = %d\n", i, temp->value);
		temp = temp->next;
	}
	printf("\n");
	temp = NULL;
}

/* Adds a link with the given value to the bag.
	param:	list pointer.
	param:	value to be added to a new Link node.
	post:	new link added to front (arbitrarily) of deque. 
*/
void linkedListAdd(struct LinkedList* list, TYPE value) {
	linkedListAddFront(list, value);
}

/*Returns 1 if a link with the value is in the deque, 0 otherwise.
	param:	list pointer.
	param:	value to be searched for.
	post:	no changes.
	returns: an int bool as appropriate.
*/
int linkedListContains(struct LinkedList* list, TYPE value) {
	int i;
	struct Link *tmp;
	tmp = list->frontSentinel->next;
	for (i = 0; LT(i, list->size); i++) {
		if (EQ(tmp->value, value)) {
			return 1;
		}
		tmp = tmp->next;
	}
	tmp = NULL;
	return 0;
}

/*Removes the first occurrence of a link with the given value.
	param:	list pointer.
	param:	value to be searched for and remvoved.
	pre:	A non empty list.
	post:	first occurence, if any, Link is removed.
	Note:	See removeLink comments.
	Note:	search halted once first occurence found.
	Note:	no effect if value not found.
*/
void linkedListRemove(struct LinkedList* list, TYPE value) {
	assert(!linkedListIsEmpty(list));
	int i;
	struct Link *temp;
	temp = list->frontSentinel->next;
	for (i = 0; LT(i, list->size); i++) {
		if (EQ(temp->value, value)) {
			removeLink(list, temp);
			break;
		}
		temp = temp->next;
	}
}
