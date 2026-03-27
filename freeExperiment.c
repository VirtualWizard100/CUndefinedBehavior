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

	struct Person *Asher = malloc(sizeof(struct Person));

	void **address = (void **) Asher;

	printf("%p\n", Asher);
	printf("%p\n", &(*address));		// The original address of Asher

	Asher->name = "Asher";
	Asher->age = 23;
	Asher->height = 5.9;

	Asher = reallocarray((void *) Asher, 2, sizeof(struct Person));		// Realloc struct Asher to be equal to the size of 2 Person structs

	struct Person *Tanjai = (Asher + 1);	// Set Tanjai at the address of the base address of Asher offset by the size of 1 Person struct to be equal to the base address of the newly allocated second Person struct

	Tanjai->name = "Tanjai";
	Tanjai->age = 25;
	Tanjai->height = 5.4;

	printf("%s\n", Asher->name);
	printf("%s\n", Tanjai->name);

	free(Asher);

//	printf("%s\n", Asher->name);	// This causes a segfault
	printf("%s\n", Tanjai->name);	// This doesn't cause a segfault?

	Tanjai = (struct Person *) &(*address);

//	printf("%s\n", Tanjai->name);	// This causes a segfault (This is Asher's old name variable)

	printf("%d\n", Tanjai->age);	// Still valid? (This is Asher's old age variable)

	printf("Next available block of memory on the heap: %016x\n", *((unsigned long long *) Tanjai));	// What?

	void *free_ptr = (void *)((unsigned long *) Tanjai);		// Assign the memory address that overwritt "Asher" to free_ptr which is the address of the next available block of memory

	printf("%p\n", free_ptr);

	memcpy(free_ptr, (void *) "Asher", 5);;

	printf("%s at address %p\n", (char *) free_ptr, free_ptr);
};
