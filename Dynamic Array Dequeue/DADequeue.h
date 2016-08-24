#ifndef DADEQUEUE
#define DADEQUEUE
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#ifndef TYPE
#define TYPE int
#endif

#ifndef LT
#define LT(a,b) (a < b)
#endif

#ifndef GT
#define GT(a,b) (a > b)
#endif

#ifndef EQ
#define EQ(a,b) (a == b)
#endif

struct deque {
	TYPE * data;
	int capacity;
	int size;
	int beg;
};

void _dequeSetCapacity(struct deque *, int);

void dequeFree(struct deque *);

void dequeInit(struct deque *, int);

int dequeSize(struct deque *);

void dequeAddFront(struct deque *, TYPE);

void dequeAddBack(struct deque *, TYPE);

TYPE dequeFront(struct deque *);

TYPE dequeBack(struct deque *);

void dequeRemoveFront(struct deque *);

void dequeRemoveBack(struct deque *);

#endif