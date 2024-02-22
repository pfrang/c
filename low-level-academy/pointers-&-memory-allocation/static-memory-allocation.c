#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 1000

struct employee_t {
  int id;
  int income;
  bool staff;
};

int initialize_employee(struct employee_t *e) {
  static int numEmployees = 0;// What the static keyword do is that only within this function it can be controlled
  numEmployees++; // because it doesnt get destroyed when the function returns it doesnt get stored on the stack saviing it ini a special place "data center"
  // this is often referred to as data hidinig as you are hiding the implementation another place
  // So when calling this function again value is not 0
  e->id = numEmployees; 
  e->income = 0;
  e->staff = false;

  return numEmployees;
};

int main()  {
  int n = 4;

  struct employee_t *employees = malloc(sizeof(struct employee_t)*n);

  if(employees == NULL) {
    printf("The allocator has failed\n");
    return -1;
  }

  for (int i = 0; i < n; i++) {
    int id = initialize_employee(&employees[i]);
    printf("New employee, ID is %d\n", id);
  } 

  free(employees);
  employees = NULL;
}
