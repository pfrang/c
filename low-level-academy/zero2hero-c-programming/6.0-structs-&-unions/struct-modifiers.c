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

__attribute__((__packed__)) struct employee_t_packed {
	int id;
	char firstname[64];
	char lastname[64];
	float income;
	bool ismanager;
};


int main() {

	struct employee_t employees[MAX_EMPLOYEES];
	struct employee_t_packed employees_packed[MAX_EMPLOYEES];

	printf("Size of employee: %lu\n", sizeof(struct employee_t)); // 140
	printf("Size of packed employees %lu\n", sizeof(struct employee_t_packed)); // 140
	// this might be important on different systems where packing structs can be done differently

}
