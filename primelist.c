#include <stdio.h>

int main() {
  /* print all the primes between 1 and 100 */
  int i,j,flag;
  for (i=2; i<100000; i++) {
    //if ((i > 2) && (i%2 == 0)) continue;
    flag = 0;
    for (j=2; j<= i/2; j++) {
      if ((i%j) == 0) {
	flag = 1;
	break;
      }
    }
    if (!flag)
      printf("%d\n", i);
  }
  return 0;
}
