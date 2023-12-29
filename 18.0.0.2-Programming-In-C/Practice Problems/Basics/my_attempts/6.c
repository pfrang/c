#include <stdio.h>

int main() {
  int x,y;

  printf("Give X int: ");
  scanf("%d", &x);
  printf("Give Y int : ");
  scanf("%d", &y);

  x = x + y;
  y = x - y;
  x = x - y;

  printf("Now %d is X and %d is Y\n", x, y);
}
