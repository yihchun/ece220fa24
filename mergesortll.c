#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  int data;
  struct node_t *next;
} node;

void ll_insert_head(node **head, int val) {
  node *tmp = malloc(sizeof(node));
  tmp->data = val;
  tmp->next = *head;
  *head = tmp;
}

node *ll_find_middle(node *head) {
  node *walk = head;
  if (head) head = head->next;
  if (head) head = head->next;
  while (head != NULL) {
    head = head->next ? head->next->next : NULL;
    walk = walk->next;
  }
  return walk;
}

node *merge(node *head1, node *head2) {
  node *res = NULL;
  /* tail points to either res (if the list is empty),
   * or to the next pointer of the tail node (if the list is nonempty),
   * so that, by changing *tail, we can append to the end of the list
   * invariant: *tail == NULL
   */
  node **tail = &res; 
    
  while (head1 && head2) {
    if (head1->data < head2->data) {
      *tail = head1;
      head1 = head1->next;
    } else {
      *tail = head2;
      head2 = head2->next;
    }
    (*tail)->next = NULL;
    tail = &((*tail)->next);
  }
  if (head1) *tail = head1;
  else *tail = head2;
  
  return res;
}

/* sorts a linked list */
void mergesort_(node **head) {
  node *middle;
  node *tmp;

  /* base case */
  if (!(*head) || !((*head)->next)) return;
  
  middle = ll_find_middle(*head);
  tmp = middle->next;
  middle->next = NULL;

  mergesort_(head);
  mergesort_(&tmp);
  *head = merge(*head, tmp);
}

void ll_print(const node *head) {
  int sum = 0;
  for (; head; head = head->next) {
    printf("%d ", head->data);
    sum += head->data;
    if (head && head->next && head->data > head->next->data)
      printf("**** ERROR ****");
  }
  printf("TOTAL %d\n", sum);
}

int main() {
  FILE *fp = fopen("/dev/urandom", "r");
  int i;
  node *head = NULL;
  for (i=0;i<100;i++) {
    ll_insert_head(&head, fgetc(fp));
    ll_print(head);
  }
  mergesort_(&head);
  ll_print(head);
  return 0;
}
  
