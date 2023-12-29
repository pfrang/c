#include <stdio.h>

int main() {

  int m;
  float km;
  // float km;
  printf("Give a km: ");
  scanf("%f", &km);

  m = km * 1000.0;

  printf("%.2fkm is %dm \n", km, m);
}
