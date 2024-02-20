#include <stdio.h>
#include <stdbool.h>
//Here, the syntax is as follows. The * character notes that the type is a pointer. The & character gets the "address of", which gets the address of x and puts that value in pX.

struct employee_t {
	int id;
	int income;
	bool staff;
};

void initialize_employee(struct employee_t *e) {
	e->id = 0;
	e->income = 0;
	e->staff = false;

	return;
};

void initialize_employee_2(struct employee_t e) {
	e.id = 100;
	e.income = 100;
	e.staff = true;	
};

int main() {
	int x = 3;
	int *pX = &x;

	printf("%d\n", *pX); // This is called dereferencing the pointer -> fetching the value
	printf("%p\n", pX);

	struct employee_t Ralph;

	// seettings the default value for Ralpg
	Ralph.id = 1;
	Ralph.income = 2;

	initialize_employee(&Ralph);

	printf("%d\n", Ralph.income); // 0

	initialize_employee_2(Ralph);

	printf("%d\n", Ralph.income); // still 0 because passing the entire struct doesnt mutate
}
