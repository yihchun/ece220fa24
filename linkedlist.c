#include <stdio.h>
#include <stdlib.h>

typedef struct llnode_t llnode;
struct llnode_t {
  int val;
  llnode *next;
};

/*
int lllength_r(const llnode *head) {
  if (!head) return 0;
  return 1+llength_r(head->next);
}
*/

int lllength(const llnode *head) {
  int ret = 0;
  /*
  for (; head; head = head->next)
    ret++;
  */
  while (head != NULL) {
    ret++;
    head = head->next;
  }
  return ret;
}

void llinsert_head(llnode **head, int val) {
  llnode *tmp = malloc(sizeof(llnode));
  tmp->val = val;
  tmp->next = *head;
  *head = tmp;
}

void llinsert_sorted(llnode **cur, int val) {
  llnode *tmp = malloc(sizeof(llnode));
  for (; *cur; cur = &((*cur)->next))
    if ((*cur)->val > val)
      break;

  tmp->val = val;
  tmp->next = *cur;
  *cur = tmp;
}

llnode *llfind(llnode *head, int val) {
  for (; head && (head->val != val); head = head->next)
    ;
  return head;
  /*
  for (; head; head = head->next)
    if (head->val == val) return head;
  return NULL;
  */
}

/* deletes the first instance of val in the linked list starting at
 * *head. Returns 1 if found, 0 if not.
 */
int llremove_first(llnode **head, int val) {
  llnode *tmp;
  for (; *head; head = &((*head)->next))
    if ((*head)->val == val)
      break;
  if (!*head)
    return 0;
  tmp = *head;
  *head = (*head)->next;
  free(tmp);
  return 1;
}

void llprint(const llnode *head) {
  for (; head; head = head->next)
    printf("%d\n", head->val);
}

int main() {
  llnode *head = NULL;
  llinsert_sorted(&head, 5);
  llinsert_sorted(&head, 7);
  llinsert_sorted(&head, 2);
  llinsert_sorted(&head, 8);
  llinsert_sorted(&head, 4);
  llinsert_sorted(&head, 1);
  llremove_first(&head, 4);
  llremove_first(&head, 10);
  llprint(head);
  return 0;
}
