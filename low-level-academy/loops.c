#include <stdio.h>

#define MAX_IDS 32

int main() {
	int i;
	for(i = 0; i < 32; i++) {
		printf("%i", i);
	}

	while(i<70) {
		printf("%i", i);
		i++;
	}

	do {
		printf("%i", i);
		i++;
	} while(i < 120);

	// task populate an array with its index


	int ids[MAX_IDS];
	printf("\n");

	int j = 0;

	for(j = 0; j < MAX_IDS; j++) {
		ids[j] = j;
		printf("%d: %d\n", j, ids[j]);
	}

	printf("Square root\n");

	for(int h = 0; h < MAX_IDS; h++) {
		ids[h] = h * h;
		printf("%d: %d\n", h, ids[h]);
	}
};
