#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	char *name;
	unsigned short age;
	double height;
};

int main(int argc, char **argv) {

	struct Person *name1 = malloc(sizeof(struct Person));

	void **address = (void **) name1;

	printf("%p\n", name1);
	printf("%p\n", &(*address));		// The original address of name1

	name1->name = "name1";
	name1->age = 23;
	name1->height = 5.9;

	name1 = reallocarray((void *) name1, 2, sizeof(struct Person));		// Realloc struct name1 to be equal to the size of 2 Person structs

	struct Person *name2 = (name1 + 1);	// Set name2 at the address of the base address of name1 offset by the size of 1 Person struct to be equal to the base address of the newly allocated second Person struct

	name2->name = "name2";
	name2->age = 25;
	name2->height = 5.4;

	printf("%s\n", name1->name);
	printf("%s\n", name2->name);

	free(name1);

//	printf("%s\n", name1->name);	// This causes a segfault
	printf("%s\n", name2->name);	// This doesn't cause a segfault?

	name2 = (struct Person *) &(*address);

//	printf("%s\n", name2->name);	// This causes a segfault (This is name1's old name variable)

	printf("%d\n", name2->age);	// Still valid? (This is name1's old age variable)

	printf("Next available block of memory on the heap: %016x\n", *((unsigned long long *) name2));	// What?

	void *free_ptr = (void *)((unsigned long *) name2);		// Assign the memory address that overwritt "name1" to free_ptr which is the address of the next available block of memory

	printf("%p\n", free_ptr);

	memcpy(free_ptr, (void *) "name1", 5);;

	printf("%s at address %p\n", (char *) free_ptr, free_ptr);
};
