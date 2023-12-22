#include <stdlib.h>
#include <stdio.h>

int main () {
  // scanf("%s", str1); //takes input
  char str1[10];
  int *age;
  int var = 3;
  age = &var;

  int *ptr;

  printf("%i\n", *age); //prints value
  printf("%p\n", &age); //prints address

  ptr = malloc(1);
  *ptr = 64382; //assigns 4 to the *ptr
  printf("%i\n", *ptr);
  int memory = sizeof(2147483647); //this is breakpoint for int 4 to 8 bytes
  printf("Memory taken %i\n", memory);

  int *ptr2 = malloc(1);
  *ptr2 = 2434343;
  printf("%i\n", *ptr2);
}
