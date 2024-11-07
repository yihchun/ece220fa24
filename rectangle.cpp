#include <iostream>
class Rectangle {
  int width, height;
public:
  Rectangle();
  Rectangle(int w, int h);
  int area();
  int getWidth() { return width; }
  int getHeight() { return height; }
};
Rectangle::Rectangle() {
  width = height = 0;
}
Rectangle::Rectangle(int w, int h) {
  width = w; height = h;
}

int Rectangle::area() { return width * height; }

int main() {
  Rectangle r(3,4);
  Rectangle b;
  std::cout << (r.getWidth() * r.getHeight()) << "\n";
  std::cout << (b.getWidth() * b.getHeight()) << "\n";
  return 0;
}
