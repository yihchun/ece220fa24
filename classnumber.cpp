class Base {
public:
  Base() { }
  virtual classno() const { return 0; }
};

class A : public Base {
public:
  A() : Base() { }
  virtual classno() const { return 1; }
};

A x;
Base *p;
int main() {
  p = &x;
  p->classno();
}
