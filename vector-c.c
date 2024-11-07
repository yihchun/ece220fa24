#include <stdio.h>
#include <math.h>

typedef struct vector_t {
  float x, y;
} vector;

vector vector_add(vector a, vector b){
  a.x += b.x;
  a.y += b.y;
  return a;
}

float vector_length(vector a) {
  return sqrt(a.x*a.x + a.y*a.y);
}

int main() {
  vector a = {3,4};
  vector b = {5,6};
  printf("%f\n", vector_length(vector_add(a,b)));
  return 0;
}
