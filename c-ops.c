#include <stdio.h>

int main() {
  int x = 3;
  int y = 5;

  printf("Both x and y are odd: %d\n", ((x%2)==1) && ((y%2)==1));
  /* (x%2) && (y%2)
     (x&y)&1
  */
  printf("x*10 is greater than y left shift 3: %d\n",
	 (x*10) > (y << 3));
  printf("Incremented x is equal to decremented y: %d\n",
	 (++x) == (--y));
}
  
