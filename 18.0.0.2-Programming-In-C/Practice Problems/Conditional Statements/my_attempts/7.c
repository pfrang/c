#include <stdio.h>
#include <stdlib.h>

int main()
{
  int num;

  printf("Give a num: ");
  scanf("%d", &num);

  if (num == 0) {
    printf("Zero\n");
    return 0;
  }

  num > 0 ? printf("Positive number") : printf("Negative number");
  return 0;
}
