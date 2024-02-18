#include <stdio.h>
#include <stdbool.h>

#define MAX_EMPLOYEES 1000
struct mystruct {
	int i;
	int c;
};

struct employee_t {
	int id;
	char firstname[64];
	char lastname[64];
	float income;
	bool ismanager;
};

int main() {
	struct mystruct mystructs[10];
	struct employee_t Fred;
	Fred.income = 100.00;
	Fred.ismanager = true;

	// an array of employees
	struct employee_t employees[10];

	int i = 0;
	for(i = 0; i < 10; i++) {
		employees[i].income = 0;
		employees[i].ismanager = false;
	}

	printf("%f\n", employees[10].income);

};
