#include <netinet/in.h>
#include "ref.h"

int protoTypeFuncExample(int); // these are 2 prototype functions
int protoTypeCall(int);

int protoTypeFuncExample(int someNumber)
{
  struct Server fwe;
  fwe.domain = 200;
  protoTypeCall(2);
  return someNumber;
}

int protoTypeCall(int num)
{
  return num;
}

int main() {
  protoTypeFuncExample(4);
}
