#include <stdio.h>
#include <stdlib.h>

int **make_pascal(unsigned int rows) {
  int **ret = malloc(rows*sizeof(int *));
  int i, j;
  for (i=0; i<rows; i++) {
    ret[i] = malloc((i+1)*sizeof(int));
    for (j=0; j<=i; j++) {
      if ((j == 0) || (j == i))
	ret[i][j] = 1;
      else
	ret[i][j] = ret[i-1][j-1]+ret[i-1][j];
    }
  }
  return ret;
}

int main() {
  int **p = make_pascal(100);
  printf("%d\n", p[50][25]);
  return 0;
}

