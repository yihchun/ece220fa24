#include <stdio.h>

#define TRY 23

int main() {
  float f = 1.0/TRY;
  float g = f;
  int i;
  for (i=1; i<=TRY; i++) {
    printf("%.16f\n", g);
    g += f;
  }
  return 0;
}
