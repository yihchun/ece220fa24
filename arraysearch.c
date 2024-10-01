#include <stdio.h>

int *find(int *a, int v, int sz) {
  int i;
  for (i=0; i<sz; i++) {
    if (*a == v)
      return a;
    a++;
  }
  return NULL;
}

int main() {
  int arr[] = {0,2,4,6,8,10,12};
  int x;
  while (1) {
    scanf("%d", &x);
    printf("%p\n", find(arr, x, 7));
  }
  return 0;
}
