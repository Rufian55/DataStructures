#ifndef Worksheet17
#define Worksheet17
#define TYPE int

struct link {
	TYPE value;
	struct link *next;
};

struct linkedListStack {
	struct link *firstLink;
};

void linkedListStackInit(struct linkedListStack *);

void linkedListStackFree(struct linkedListStack *);

void linkedListStackPush(struct linkedListStack *, TYPE);

TYPE	linkedListStackTop(struct linkedListStack *);

void linkedListStackPop(struct linkedListStack *);

int linkedListStackIsEmpty(struct linkedListStack *);

#endif