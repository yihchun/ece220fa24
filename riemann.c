#include <stdio.h>
#include <math.h>

float f(float x) {
  return sin(x);
}

float riemann(float start, float end, unsigned int N) {
  float inc = (end-start)/N;
  float left;
  float area = 0;
  int i;
  for (i=0; i<N; i++) {
    left = start+inc*i;
    area += f(left) * inc;
  }
  return area;
}

int main() {
  printf("%f\n", riemann(0,3.14159265f/2.0,10000));
}
