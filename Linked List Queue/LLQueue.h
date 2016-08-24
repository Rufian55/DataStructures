#ifndef LLQUEUE
#define LLQUEUE

#ifndef TYPE
#define TYPE int
#endif

struct link {
	TYPE value;
	struct link *next;
};

struct listQueue {
	struct link *firstLink;
	struct link *lastLink;
};

void listQueueInit(struct listQueue *);

void listQueueFree(struct listQueue *);

void listQueueAddBack(struct listQueue *, TYPE);

TYPE listQueueFront(struct listQueue *);

void listQueueRemoveFront(struct listQueue *);

int listQueueIsEmpty(struct listQueue *);

#endif