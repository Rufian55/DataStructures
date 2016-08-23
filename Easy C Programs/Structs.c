#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct myStruct {
	int var_1;
	int var_2;
};

struct myStruct* allocMem() {
	struct myStruct *ptr = (struct myStruct *)malloc(sizeof(struct myStruct) * 3);
	return ptr;
}

void fillStructs(struct myStruct* aStruct) {
	aStruct->var_1 = 1;
	aStruct->var_2 = 11;

	(aStruct + 1)->var_1 = 2;
	(aStruct + 1)->var_2 = 22;

	(aStruct + 2)->var_1 = 3;
	(aStruct + 2)->var_2 = 33;

}

void printStruct(struct myStruct* aStruct) {
	int i;
	for (i = 0; i < 3; i++) {
		printf("%i %i\n", (aStruct + i)->var_1, (aStruct + i)->var_2);
	}
}

int main() {
	struct myStruct* theStruct = NULL;

	theStruct = allocMem();

	fillStructs(theStruct);

	printStruct(theStruct);

	return 0;
}