#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_EMPLOYEES 1000

struct employee_t {
  int id;
  int income;
  bool staff;
};

void initialize_employee(struct employee_t *e) {
  e->id = 423;
  e->income = 0;
  e->staff = false;

  return;
};

int main() {

  struct employee_t employees[MAX_EMPLOYEES];

  initialize_employee(&employees[0]);

  printf("%d\n", employees[0].id);

  // Alternative way - the above is bad because 1000 structs is created in memory

  // this would effectively be the same as above
  struct employee_t *employees1 = malloc(sizeof(struct employee_t)* MAX_EMPLOYEES);

  // to be more memory efficient do below
  // instead create a runtime value to dynamically allocate how much memory you need with n
  int n = 4;
  struct employee_t *employees2 = malloc(sizeof(struct employee_t)*n);
  if (employees2 == NULL) {
    printf("The allocator failed\n"); // This can apparently happen
    return -1;
  }

  initialize_employee(&employees2[0]);

  printf("%d\n", employees2[0].id); // Also 432
  free(employees2);
  employees2 = NULL; // This is best practice to prevent referencing this struct again as it will break the program
  
  // TLDR: the int 4 is dynaic memory allocationø. Instead of relying at compile time values for allocating memory
  // we are dynamically updating based on runtime values
}
