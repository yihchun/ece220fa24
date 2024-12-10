#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode_t {
  int val;
  struct treeNode_t *left;
  struct treeNode_t *right;
} treeNode;

void tree_insert(treeNode **root, int v) {
  if (*root == NULL) {
    *root = malloc(sizeof(treeNode));
    (*root)->val = v;
    (*root)->left = (*root)->right = NULL;
    return;
  }
  if ((*root)->val == v) return;
  if (v > (*root)->val) {
    tree_insert(&(*root)->right, v);
  } else {
    tree_insert(&(*root)->left, v);
  }
}

int tree_find(const treeNode *root, int v) {
  if (!root) return 0;
  if (root->val == v) return 1;
  if (v > root->val)
    return tree_find(root->right, v);
  else
    return tree_find(root->left, v);
}

void tree_inorder(const treeNode *root) {
  if (!root) return;
  tree_inorder(root->left);
  printf("%d\n", root->val);
  tree_inorder(root->right);
}

int main() {
  treeNode *root = NULL;
  FILE *fp = fopen("/dev/urandom", "r");
  int i;
  for (i=0; i<64; i++) tree_insert(&root, fgetc(fp));
  tree_inorder(root);
  return 0;
}

