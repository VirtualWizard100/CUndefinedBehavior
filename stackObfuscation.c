#include <stdio.h>

int obfuscation(int a) {

	int b = 5;
	a += b;
	return b;
};

void realFunc(void) {

	int c, d;

	printf("%d\n", c);
	printf("%d\n", d);

};

int main(void) {

	obfuscation(10);

	realFunc();

	realFunc();
};
