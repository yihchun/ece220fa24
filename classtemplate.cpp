#include <iostream>
using namespace std;

template <class T, class Q>
class mypair {
	T a, b;
  Q c;
	public:
	mypair (T first, T second)
		{a=first; b=second;}
	T getmax ();
};

template <class T, class Q>
T mypair<T,Q>::getmax () {
	T retval;
	retval = a>b? a : b;
	return retval;
}

class foo {
  //int operator>(const foo &x) const { return 0; }
};

int main () {
  foo a,b;
  mypair <foo, int> myobject (a, b);
  //myobject.getmax();
  //cout << myobject.getmax();
	return 0;
}
