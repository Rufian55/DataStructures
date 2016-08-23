#ifndef COMPARE_H
#define COMPARE_H

#include <stdio.h>

struct data {
	int number;
	char *name;
};

int compare(void *, void *);

void printVal(void *);

void printName(void *);

#endif