#include <stdio.h>

int addTwoNumbers(int n1, int n2);

int main() {
  int nr1 = 1;
  int nr2 = 2;

  int sum = addTwoNumbers(nr1, nr2);
  printf("%d\n", sum);
}

int addTwoNumbers(int n1, int n2) {
  return n1 + n2;
}
