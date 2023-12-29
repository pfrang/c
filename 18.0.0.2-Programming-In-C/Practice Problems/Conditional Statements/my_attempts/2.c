
#include <stdio.h>

int main()
{
  int m, v;

  printf("Give number 1: ");
  scanf("%d", &m);

  printf("Give number 2: ");
  scanf("%d", &v);

  if (m > v)
  {
    printf("%d is bigger than %d\n", m,v);
  }
  else if(v < m)
  {
    printf("%d is bigger than %d\n", v,m);
  } else {
    printf("They are equal");
  }
}
