#include <iostream>

class Shape {
protected:
  double width, height;
public:
  Shape() { std::cout << "Calling Shape constructor\n"; width = 1; height = 1;}
  Shape(double a, double b) { width = a; height = b; }
  virtual double area() const=0;
  void show() const { std::cout << "I am a shape of size " << width << " x " << height << std::endl; }
};

class Triangle : public Shape {
public:
  Triangle() { }
  Triangle(double a, double b) : Shape(a,b) { }
  double area() const { return 0.5*width*height; }
};

class Rectangle : public Shape {
public:
  Rectangle() { }
  Rectangle(double a, double b) : Shape(a,b) { }
  double area() const { return width*height; }
};

class IndeterminateShape : public Shape {
public:
  IndeterminateShape() { }
  IndeterminateShape(double a, double b) : Shape(a,b) { }
};

class SuperTriangle : public Triangle {
public:
  SuperTriangle(double a, double b) : Triangle(a,b) { }
  double area() const { return -1; }
};

int main() {
  Triangle t(3,4);
  Rectangle r(5,6);
  Triangle *x = new SuperTriangle(7,8);
  Shape *s = x;
  s = new IndeterminateShape();
  //Shape *s = new Shape(7,8);
  std::cout << "Triangle Area: " << t.area() << std::endl;
  std::cout << "Rectangle Area: " << r.area() << std::endl;
  std::cout << "Shape Area: " << s->area() << std::endl;
  std::cout << "X Area: " << x->area() << std::endl;
  s = new Rectangle(1,2);
  std::cout << "Shape Area: " << s->area() << std::endl;
  
  t.show();
  r.show();
  return 0;
}

  
