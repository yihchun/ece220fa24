#include <stdio.h>

int Fact(unsigned int n);
unsigned int multiply(unsigned int b, unsigned int a) {
  unsigned int i, accum;
  accum = 0;
  for (i=1; i; i <<= 1) {
    if (a & i)
      accum += b;
    b <<= 1;
  }
  return accum;
}
  
int main() {
  unsigned int x;
  scanf("%u", &x);
  printf("%d\n", Fact(x));
}

int Fact(unsigned int n) {
  int total = 1;
  while (n > 0) {
    total = multiply(n, total);
    n--;
  }
  return total;
}

