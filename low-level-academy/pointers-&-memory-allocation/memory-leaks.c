#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct some_struct {
  int id;
  int hey;
};

long hello(long *ptr) {
  return 2;
}

int main() {
  
  int h = 3243242;
  struct some_struct *heuu = malloc(sizeof(struct some_struct) * 1000);
  // Compile the code with gcc -o program code.c -g the debug flag to check for memory leaks
  // valgrind --leak-check=full ./program Run with valgrind to check
  printf("%p\n", heuu);
 
  // If this free is not added, there will be error indication in valgrind check
  free(heuu); 
} 
