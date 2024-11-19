#include <iostream>
using namespace std;

template <class T>
class BST {
  class BSTNode;
public:
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
  BST<int> tree;
  tree.insert(5);
  tree.insert(1);
  tree.insert(3);
  tree.insert(2);
  tree.insert(8);
  BST<int> tree2(tree);
  tree.remove(5);
  for (int i=0; i<10; i++)
    cout << i << " " << tree.find(i) << endl;
}
