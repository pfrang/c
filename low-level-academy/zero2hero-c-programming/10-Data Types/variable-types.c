#include <stdio.h>

int main(int argc, char *argv[]) {
  int x;

  char y;  // 1 byte, 8 bits
  short s; // 2 bytes 16 bits
  int i;   // 4 bytes, 32 bits
  // an int can only go up to 2^31 - 1
  unsigned int xx; // while this can go up to 2^32 because the first byte isnt
                   // reservced for negative or minus
  long long int l; // 8 byte, 64 bit

  float f = 3.14;
  double d =
      3.14159; // You want to use double instead of float due to precision
  printf("sizeof float %lu sizeof double %lu\n", sizeof(float), sizeof(double));
  long idLong;
  unsigned long idUlLong;
}
