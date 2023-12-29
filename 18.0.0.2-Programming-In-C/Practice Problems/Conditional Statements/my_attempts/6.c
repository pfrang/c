#include <stdio.h>

int main()
{
  int num;

  printf("Give a num: ");
  scanf("%d", &num);

  num % 2 == 0 ? printf("Even number") : printf("Odd number");
  return 0;
}
