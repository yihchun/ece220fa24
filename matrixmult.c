#include <stdio.h>

void matrixmult(float *c, float *a, float *b, int ar, int br, int bc) {
  int i, j, k;
  for (i=0; i<ar; i++) {
    for (j=0; j<bc; j++) {
      /* populate c[i][j] */
      c[i*bc+j] = 0;
      for (k=0; k<br; k++) {
	c[i*bc+j] += a[i*br+k] * b[k*bc+j];
	  /* a[i][k] * b[k][j] */
      }
    }
  }
}
void showmatrix(float *m, int r, int c) {
  int i, j;
  for (i=0; i<r; i++) {
    for (j=0; j<c; j++) {
      printf("%f ", m[i*c+j]);
    }
    printf("\n");
  }
}
int main() {
  float a[2][3] = {1,2,3,4,5,6};
  float b[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
  float c[2][4];
  matrixmult(c[0],a[0],b[0],2,3,4);
  showmatrix(c[0],2,4);
}
