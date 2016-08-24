/***************************************************************************************
** LList_Iterator.c
** Author: Chris Kearns
** A linked list deque implementation
** Compile with:
** gcc -Wall -std=c99 LList.h LList.c LList_iterator.h LList_Iterator.c -o LLitr
****************************************************************************************/
#include "LList_Iterator.h"


void linkedListIteratorInit(struct linkedList *lst, struct linkedListIterator * itr) {
	itr->lst = lst;
	itr->currentLink = itr->lst->frontSentinel;
}


int linkedListIteratorHasNext(struct linkedListIterator *itr) {
	if(itr->currentLink->next != itr->lst->backSentinel){
		itr->currentLink = itr->currentLink->next;
		return 1;
	}
	else
		return 0;
}


TYPE linkedListIteratorNext(struct linkedListIterator *itr) {
	return(itr->currentLink->value);
}


void linkedListIteratorRemove(struct linkedListIterator *itr){
	struct dlink *tmp = itr->currentLink;
	itr->currentLink = itr->currentLink->prev;
	_removeLink(itr->lst, tmp);
}

int main(int argc, char* argv[]) {
	struct linkedList aLList;
	struct linkedList *LL = 0;
	LL = &aLList;
	LinkedListInit(LL);

	printf("Call to LinkedListIsEmpty returns %d\n", LinkedListIsEmpty(LL));
	LinkedListAddBack(LL, 10);
	LinkedListAddBack(LL, 20);
	LinkedListAddFront(LL, 5);
	LinkedListAddBack(LL, 30);
	LinkedListAddBack(LL, 40);

	struct linkedListIterator *itr;
	TYPE current;
	linkedListIteratorInit(LL, itr);

	while (linkedListIteratorHasNext(itr)) {
		current = linkedListIteratorNext(itr);
		printf("current = %d\n", current);
		linkedListIteratorRemove(itr);
	}

	LinkedListFree(LL);

	return 0;
}