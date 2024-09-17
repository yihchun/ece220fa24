#include <stdio.h>

int Fact(unsigned int n);

int main() {
  unsigned int x;
  scanf("%u", &x);
  printf("%d\n", Fact(x));
}

int Fact(unsigned int n) {
  int total = 1;
  while (n > 0) {
    total *= n;
    n--;
  }
  return total;
}

