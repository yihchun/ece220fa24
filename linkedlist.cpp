#include <iostream>

template <class T>
class LList;

template <class T>
class LLNode {
  public:
  friend class LList<T>;
  T data;
  LLNode(T new_data){
    data = new_data; next = NULL; 
  }
  ~LLNode() { delete next; }
private:
  LLNode(T new_data, LLNode<T> *n) {
    data = new_data; next = n;
  }
  LLNode<T> *next;
};

template <class T>
class LList {
public:
  LList() { head = NULL; }
  ~LList() { delete head;
    /*
    LLNode<T> *walk, *tmp;
    for (walk = head; walk; walk = tmp) {
      tmp = walk->next;
      delete walk;
    }
    */
  }

  void add(T val) {
    /*
    LLNode<T> *tmp = new LLNode<T>(val);
    tmp->next = head;
    head = tmp;
    */
    head = new LLNode<T>(val, head);
    std::cout << "updating head to " << head << "\n";
  }

  LList<T> &operator=(const LList<T> &src) {
    LLNode<T> *walk;
    LLNode<T> **anotherptr = &head;
    delete head; // deallocate existing nodes in our list, else they will become garbage
    head = NULL; // reinitialize head, else if src is empty, head is dangling
    /* two ways to do this
     * 1 has two cases: either update head, or update tail->next
     * the other way is with double pointers
     */
    for (walk = src.head; walk; walk = walk->next) {
      *anotherptr = new LLNode<T>(walk->data);
      std::cout << "adding to list " << *anotherptr << "\n";
      anotherptr = &((*anotherptr)->next);
    }
    return *this;
  }
  
  void show(std::ostream &os = std::cout) const {
     LLNode<T> *walk;
     for (walk = head; walk; walk = walk->next) {
       os << walk->data << " ";
     }
     os << std::endl;
  }

  
  class LLIterator : public std::iterator<std::forward_iterator_tag, T> {
  public:
    LLIterator() { ptr = NULL; }
    LLIterator(LLNode<T> *h) { ptr = h; }
    LLIterator(const LLIterator &src) { ptr = src.ptr; }
    LLIterator &operator=(const LLIterator &src) { ptr = src.ptr; }
    int operator==(const LLIterator &src) const { return ptr == src.ptr; }
    int operator!=(const LLIterator &src) const { return ptr != src.ptr; }
    LLIterator operator++() { ptr = ptr->next; return *this; } // preincrement
    LLIterator operator++(int) { LLIterator tmp(*this); ptr = ptr->next; return tmp; } //postincr
    T &operator*() { return ptr->data; } // as lvalue
    T operator*() const { return ptr->data; } // as rvalue
  private:
    LLNode<T> *ptr;
  };
  
  LLIterator begin() {
    LLIterator ret(head);
    return ret;
  }

  LLIterator end() {
    LLIterator ret;
    return ret;
  }
private:
  LLNode<T> *head;
};

template <class T>
std::ostream& operator<<(std::ostream & stream, const LList<T> & list) {
  list.show(stream);
  return stream;
}

void foo() {
  LList<int> x;
  LList<int> y;
  x.add(1);
  x.add(2);
  x.add(3);
  y.add(9);
  y=x;
  std::cout << y;
  /*
  for (LList<int>::LLIterator it=x.begin(); it != x.end(); it++)
    std::cout << *it << " ";
  */
}

int main() {
  foo();
  return 0;
}
  
