#include <stdio.h>

int main() {

  int m;
  float km;
  printf("Give a meter: ");
  scanf("%d", &m);

  km = m / 1000.0;

  printf("%d is %.3fkm \n", m, km);
}
