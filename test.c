#include <stdio.h>

int f() {
	return (0);
}

int main(void) {
	int(*g)(void);
	g = f;
}
