#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

template <class T>
class ptr_shared {
  class control_block {
  public:
    control_block(T *p, unsigned int c = 1) { ptr = p; count = c; }
    T *ptr;
    unsigned int count;
  };
  /* if we have a pointer, put it inside a control block,
   * so every reference to the same pointer holds the same count.
   * NULL (nullptr) doesn't need a control block, so just use
   * ctrl == NULL for the null pointer.
   */
  control_block *ctrl;
  
  void decrement_count(control_block *c) {
    if (!c) return;
    if (!--c->count) {
      cout << "deleting " << c->ptr << endl;
      delete c->ptr;
      delete c;
    }
  }

public:
  ptr_shared() { ctrl = nullptr; }
  ptr_shared(const ptr_shared &p) {
    ctrl = p.ctrl;
    if (ctrl) ctrl->count++;
  }
  ptr_shared(T *p) { if (p) ctrl = new control_block(p); else ctrl = nullptr; }
  ~ptr_shared() { decrement_count(ctrl); }
  int operator==(T *p) {
    if (!ctrl) return p==nullptr;
    return ctrl->ptr == p; }
  const ptr_shared &operator=(const ptr_shared &p) {
    control_block *c = ctrl;
    ctrl = p.ctrl;
    if (ctrl) ctrl->count++;
    decrement_count(c);
    return *this;
  }
  const ptr_shared &operator=(T *p) {
    control_block *c = ctrl;
    if (p) ctrl = new control_block(p);
    else ctrl = nullptr;
    decrement_count(c);
    return *this;
  }
  T &operator*() { return *ctrl->ptr; }
  T *operator->() { return ctrl->ptr; }
};

template <class T>
class LLStack {
  class Node {
  public:
    Node(const T &v, ptr_shared<Node> n) : val(v), next(n) { }
    Node(const T &v, Node *n) : val(v), next(n) { }
    T val;
    ptr_shared<Node> next;
  };
  ptr_shared<Node> head;
public:
  LLStack() { }
  LLStack(const LLStack &src) { head = src.head; }
  int operator==(const LLStack &src) {
    ptr_shared<Node> walk1, walk2;
    walk1 = head;
    walk2 = src.head;
    while (1) {
      if (walk1 == nullptr) return walk2 == nullptr;
      if (walk2 == nullptr) return 0;
      if (walk1->val != walk2->val) return 0;
      walk1 = walk1->next;
      walk2 = walk2->next;
    }
    return 1;
  }
  const LLStack &operator=(const LLStack &src) { head = src.head; }
  void push(const T &v) { head = new Node(v, head); }
  T pop() {
    /*
    T ret = head->val;
    head = head->next;
    return ret;
    */
    ptr_shared<Node> tmp(head);
    head = head->next;
    return tmp->val;
  }
};

template <class T, class U>
class mypair {
public:
  mypair(const T &f, const U &s) : first(f), second(s) { }
  T first;
  U second;
};

template <class T>
class BST {
  class BSTNode;
public:
  class Iterator {
  public:
    Iterator() {  }
    Iterator(const Iterator &src) { }
    Iterator &operator=(const Iterator &src) { }
    int operator==(const Iterator &src) const { }
    int operator!=(const Iterator &src) const { }
    Iterator operator++() { } // preincrement
    Iterator operator++(int) { } //postincr
    T &operator*() {  } // as lvalue
    T operator*() const {  } // as rvalue
  private:
    LLStack<mypair<BSTNode *,int> > loc;
  };

  BST() { root = NULL; }
  BST(const BST &src) { root = copy_subtree(src.root);  }
  ~BST() { delete_subtree(root); }
  const BST &operator=(const BST &src) {
    delete_subtree(root);
    root = copy_subtree(src.root);
  }
  void insert(const T &data) {
    if (root == NULL) {
      root = new BSTNode(data);
      return;
    }
    BSTNode *walk = root;
    while (walk != NULL) {
      if (walk->data < data) {
	if (!walk->right) {
	  walk->right = new BSTNode(data);
	  return;
	}
	walk = walk->right;
      } else {
	if (!walk->left) {
	  walk->left = new BSTNode(data);
	  return;
	}
	walk = walk->left;
      }
    }
  }
  int remove(const T &data) {
    BSTNode **victim = &root;
    while (*victim != NULL) {
      if ((*victim)->data == data) break;
      if ((*victim)->data < data)
	victim = &((*victim)->right);
      else
	victim = &((*victim)->left);
    }
    if (!*victim) return 0;
    if ((*victim)->left && (*victim)->right) {
      BSTNode **donor = &((*victim)->left);
      while ((*donor)->right)
	donor = &((*donor)->right);
      (*victim)->data = (*donor)->data;
      victim = donor;
    }
    BSTNode *tmp = *victim;
    *victim = tmp->left;
    if (!*victim)
      *victim = tmp->right;
    /* *victim = tmp->left ? tmp->left : tmp->right */
    delete tmp;
    return 1;
  }

  int find(const T &data) const {
    BSTNode *walk = root;
    while (walk != NULL) {
      if (walk->data == data) return 1;
      if (walk->data < data)
	walk = walk->right;
      else
	walk = walk->left;
    }
    return 0;
  }
private:
  void delete_subtree(BSTNode *r) {
    if (!r) return;
    cerr << "Deleting subtree " << r << " val " << r->data << endl;
    delete_subtree(r->left);
    delete_subtree(r->right);
    delete r;
  }
  BSTNode *copy_subtree(BSTNode *r) {
    if (!r) return NULL;
    return new BSTNode(r->data, copy_subtree(r->left), copy_subtree(r->right));
  }
  class BSTNode {
  public:
    BSTNode() : data() { left = right = NULL; }
    BSTNode(const T &d) : data(d) { left = right = NULL; }
    BSTNode(const T &d, BSTNode *l, BSTNode *r) : data(d) { left=l; right=r; }
    T data;
    BSTNode *left, *right;
  };
  BSTNode *root;
};

int main() {
  LLStack<int> s;
  s.push(5);
  s.push(3);
  s.push(2);
  LLStack<int> r(s);
  cout << (r == s) << endl;
  cout << s.pop() << endl;
  cout << (r == s) << endl;
  s.push(1);
  cout << s.pop() << endl;
  cout << r.pop() << endl;
  cout << r.pop() << endl;
}
