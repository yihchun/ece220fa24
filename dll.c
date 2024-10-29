#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* HW: write insert_sorted, edit to have head & tail ptrs in a struct */

typedef struct dllnode_t dllnode;
struct dllnode_t {
  int val;
  dllnode *next;
  dllnode *prev;
};

void dll_verify(const dllnode *head) {
  assert(head->prev == NULL);
  while ((head = head->next)) {
    assert(head->prev->next == head);
  }
}

void dll_insert_head(dllnode **head, int val) {
  dllnode *tmp = malloc(sizeof(dllnode));
  tmp->val = val;
  tmp->prev = NULL; /* one place insert_sorted changes */
  if (*head)
    (*head)->prev = tmp;
  tmp->next = *head;
  *head = tmp;
}

int dll_delete_first(dllnode **head, int val) {
  dllnode *tmp;
  dllnode *prev;
  for (tmp = *head; tmp->val != val; tmp = tmp->next)
    ;
  if (!tmp) return 0;
  if (tmp->prev) {
    prev = tmp->prev;
    tmp->prev->next = tmp->next;
  } else {
    prev = NULL;
    *head = tmp->next;
  }
  if (tmp->next)
    tmp->next->prev = prev;
  free(tmp);

  return 1;
}

int main() {
  dllnode *head = NULL;
  dll_insert_head(&head, 5);
  dll_insert_head(&head, 3);
  dll_insert_head(&head, 1);
  dll_verify(head);
  return 0;
}
