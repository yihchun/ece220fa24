#include <iostream>
#include <math.h>

/* implicit variables in every instance method (or constructor/destructor):
 *   this -- pointer to the current object
 *   instance variables -- reference them directly
 */
class vector {
public:
  vector() { x = y = 0; }
  vector(float x_, float y_) {
    x = x_; y = y_;
  }
  ~vector() {
    std::cout << "goodbye " << this << std::endl;
  }
  vector addTo(const vector &b) {
    x += b.x;
    y += b.y;
    return *this;
  }
  vector operator+(const vector &b) const {
    vector r;
    r.x = x+b.x;
    r.y = y+b.y;
    return r;
  }
  vector &operator=(const vector &a) {
    x = a.x; y = a.y;
    return *this;
  }
  /* a = b = c;
   * a = (b=c);
   * a.operator=(b.operator=(c));
   */

  int operator==(const vector &a) const {
    return (x == a.x) && (y == a.y);
  }

  float length() const {
    return sqrt(x*x+y*y);
  }
private:
  float x, y;
};

void swap(int &a, int &b) { int tmp =a; a=b; b=tmp; }
int deref(int *a) { return *a; }
int sum(int a, int b) { return a+b; }
float sum(float a, float b) { return a+b;}

/* objects are kind of like structs in C
 * except that they have methods that you can call on them
 * those methods look like struct elements (they are not:
 *   there is not a separate copy of the method code for each object)
 */
int main() {
  vector a(3,4);
  vector b(5,6);
  vector d;
  vector *c = new vector(7,8);
  delete c;
  c = new vector[10];
  delete [] c;
  d = a+b; /* d.operator=(a.operator+(b)); */
  std::cout << d.length() << std::endl;
  return 0;
}
