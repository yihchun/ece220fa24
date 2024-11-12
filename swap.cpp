
template <class T>
void swap(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

int main() {
  float x, y;
  swap<float>(x, y);
  swap(x, y);
  return 0;
}
