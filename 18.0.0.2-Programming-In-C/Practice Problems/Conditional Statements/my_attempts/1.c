
#include <stdio.h>

int main() {
  int m,v;

  printf("Give number 1: ");
  scanf("%d", &m);

  printf("Give number 2: ");
  scanf("%d", &v);

  if(m == v) {
    printf("Equal\n");
  } else {
    printf("Different\n");
  }
}
