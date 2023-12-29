#include <stdio.h>

int main()
{
  int a, b;

  printf("Give number A: ");
  scanf("%d", &a);

  printf("Give number B: ");
  scanf("%d", &b);

  a > b ? printf("%d A is bigger than %d B\n", a, b) : printf("%d B is bigger than %d A\n", b, a);
  return 0;
}
