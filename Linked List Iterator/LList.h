#ifndef LLIST
#define LLIST

#ifndef TYPE
#define TYPE int
#endif

struct dlink {
	TYPE value;
	struct dlink *next;
	struct dlink *prev;
};

struct linkedList {
	int size;
	struct dlink *frontSentinel;
	struct dlink *backSentinel;
};

void LinkedListInit(struct linkedList *);

void LinkedListFree(struct linkedList *);

void LinkedListAddFront(struct linkedList *, TYPE);

void LinkedListAddBack(struct linkedList *, TYPE);

void LinkedListRemoveFront(struct linkedList *);

void LinkedListRemoveBack(struct linkedList *);

int LinkedListIsEmpty(struct linkedList *);

TYPE LinkedListFront(struct linkedList *);

TYPE LinkedListBack(struct linkedList *);

void _addBefore(struct linkedList *, struct dlink *, TYPE);

void _removeLink(struct linkedList *, struct dlink *);

#endif