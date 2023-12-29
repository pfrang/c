#include <stdio.h>

int main() {
  int year;

  printf("Give a year: ");
  scanf("%d", &year);

  year%4== 0 ? printf("Leap year") : printf("Not a leap year");
  return 0;
}
