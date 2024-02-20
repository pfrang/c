#include <stdio.h>
#include <stdbool.h>

#define MAX_EMPLOYEES 1000

struct employee_t {
	int id;
	char firstname[64];
	char lastname[64];
	float income;
	bool ismanager;
};

// unions are  a field that assign multiple labels
// of multiple types to the same memory location
// It will only allocate the memory of the largest element
// 4 bytes in the example below
union my_union {
	int x;
	char c; // 1 byte
	short s; // 2 bytes
};

int main() {
	struct employee_t employees[MAX_EMPLOYEES];	

	union my_union u;

	u.x = 0x41424344;

	printf("%hx %hx\n", u.c, u.s); 
	// outputs 43 4344 because a union is only allocating
	// the least memory necessary so we are accessing x's values basically
}
