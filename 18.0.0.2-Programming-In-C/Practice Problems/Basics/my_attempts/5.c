#include <stdio.h>

int main() {
  int a,b,c;

  printf("Give a int: ");
  scanf("%d", &a);
  printf("Give b int : ");
  scanf("%d", &b);

  c = a;
  a = b;
  b = c;

  printf("Now %d is B and %d is A\n", b, a);
}
