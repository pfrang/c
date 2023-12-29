#include <stdio.h>

float meter_to_feet(int meter);

int main() {
  int m;
  float result;
  printf("Give meter: ");
  scanf("%d", &m);

  result = meter_to_feet(m);

  printf("%d meter is %.2f feet\n", m, result);
}


float meter_to_feet(int meter) {
  return meter / 0.3048;
}
