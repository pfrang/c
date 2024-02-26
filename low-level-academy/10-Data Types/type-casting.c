#include <stdio.h>

int main(int argc, char *argv[]) {

  unsigned int x = 4;

  int signedX = (int)(x);

  unsigned int bigx = 0xfffffefe;
  // We are basically here requesting 32 bits to be stored in 16 bits so we will
  // lose the first 4 chars, 0xffff
  printf("%lu\n", sizeof(short));
  short kindabig = (short)bigx;

  // what about the opposite
  short short2 =
      -1; // oxffff == What negative values do is turn all 0 to 1 (lol sick)
  int wasashort = (int)short2; // what will happen here is that it will just
                               // extend the number to 0xffffffff

  float f = 3.14;
  int wasafloat = (int)float; // An assembly instruction to round the float

  short *mydata = (short *)argv[1];
}
