#include <stdio.h>

void print_num(int x) {
  printf("%d\n", x);
}

int main() {
  int x = (int)3.14f;
  print_num((int)3.14f);
  printf("%d\n", (int)3.14f);
}
