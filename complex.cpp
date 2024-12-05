#include <iostream>

class Complex {
  double real, imag;
public:
  Complex() {real = imag = 0;}
  Complex(double r_, double i_) { real = r_; imag = i_; }
  Complex(const Complex &c) { real = c.real; imag = c.imag; }
  Complex &operator=(const Complex &c) { real = c.real; imag = c.imag; return *this;}
  Complex operator+(const Complex &c) const { return Complex(real+c.real, imag+c.imag); }
  Complex operator-(const Complex &c) const { return Complex(real-c.real, imag-c.imag); }
  Complex operator*(const Complex &c) const { return Complex(real*c.real-imag*c.imag, imag*c.real+real*c.imag); }
  Complex operator/(const Complex &c) const {
    double denom = c.real*c.real+c.imag*c.imag;
    return Complex((real*c.real+imag*c.imag)/denom,
		   (imag*c.real-real*c.imag)/denom); }
  Complex operator/(double d) const {
    return Complex(real/d, imag/d);
  }
  friend std::ostream &operator<<(std::ostream &os, const Complex &c);
};

std::ostream &operator<<(std::ostream &os, const Complex &c) {
  return os << c.real << "+" << c.imag << "i";
}


int main() {
  Complex a(1,2);
  Complex b(3,4);
  Complex c;
  c = a*b;
  (a = b) = c;
  std::cout << c << std::endl;
  std::cout << ((a = b) = c) << std::endl;
  std::cout << a << std::endl;
}
