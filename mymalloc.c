#include <stdio.h>
#include <sys/mman.h>
#include <assert.h>

#define MIN_SIZE_TO_ASK_FOR 16*1024*1024

/* ask the OS for len bytes of memory */
void *get_from_OS(size_t len) {
  return mmap(0, len, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
}

typedef struct mymalloc_header_t mymalloc_hdr;
struct mymalloc_header_t {
  size_t size;
  mymalloc_hdr *next;
};

mymalloc_hdr *freelist;

void *ask_os_for(size_t len) {
  if (len < MIN_SIZE_TO_ASK_FOR)
    len = MIN_SIZE_TO_ASK_FOR;
  return get_from_OS(len);
}

void *mymalloc(size_t len) {
  mymalloc_hdr *w1, *w2 = NULL;
  for (w1 = freelist; w1; w1 = w1->next) {
    if (w1->size >= (len+sizeof(size_t)))
      break;
    w2 = w1;
  }
  if (w1) {
    if (w2) {
      w2->next = w1->next; /* removes w1 from the linked list */
    } else {
      freelist = w1->next;
    }
    /* it might be nice to split w1 if there's enough space */
    return &(w1->next);
  } else {
    w1 = ask_os_for(len + sizeof(size_t));
    /* it might be nice to split w1 if there's enough space */
    return &(w1->next);
  }
}

void myfree(void *something) {
  size_t *sth = something;
  mymalloc_hdr *tmp = (mymalloc_hdr*) (sth-1);
  tmp->next = freelist;
  freelist = tmp;
}

/* TODO
 * split space in the free list when the chunk is too big
 * pick a better chunk (first-fit vs best-fit)
 * combine chunks that are adjacent in the free list
 * realloc
 */
