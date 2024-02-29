#include <stdio.h>

int main(int argc, char *argv[]) {

  // same size
  unsigned int x = 4;
  int signedX = (int)(x);

  unsigned int bigx = 0xfffffefe;
  // We are basically here requesting 32 bits to be stored in 16 bits so we will
  // lose the first 4 chars, 0xffff
  printf("%lu\n", sizeof(short));
  // downcasting
  short kindabig = (short)bigx;

  // what about the opposite
  short short2 = -1; // oxffff == What negative values do is turn all 0 to 1
                     // (lol sick)
  // upcasting
  int wasashort = (int)short2; // what will happen here is that it will just
                               // extend the number to 0xffffffff

  // Signedness Casting
  int other_var = -1;
  unsigned int y =
      (unsigned int)other_var; // This will be converted to max_int 42949672951
  printf("%ui", y);
  // crosscasting
  float f = 3.14;
  int wasafloat = (int)f; // An assembly instruction to round the float

  short *mydata = (short *)argv[1];
}
