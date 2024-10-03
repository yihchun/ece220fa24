#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

void print_array(int *a, int sz);
/* find takes an array a of size sz and looks for a value v in it.
 * if found, returns a pointer to that value, otherwise returns NULL
 */
int *find(int *a, int v, int sz) {
  int i;
  for (i=0; i<sz; i++) {
    if (*a == v)
      return a;
    a++;
  }
  return NULL;
}

/* find takes an array a of size sz with values in increasing order
 * and looks for a value v in it.
 * if found, returns a pointer to that value, otherwise returns NULL
 */
int *binaryfind(int *a, int v, int sz) {
  int left, right, mid;
  left = 0;
  right = sz-1;
  /* we are looking for v in the closed interval (includes the indices
   * specified) between [left, right]
   * keep looping while the interval is non-empty
   */
  while (left <= right) {
    mid = (left+right)/2;
    if (a[mid] == v)
      return &a[mid];
    if (a[mid] < v) {
      left = mid+1;
    } else {
      right = mid-1;
    }
  }
  return NULL;
}

/* bubble-sort: iterate through the array sz-1 times
 * each time through the array, you swap the two neighbors
 * if they're out of order
 * so named because smallest values "bubble" to the top
 */
void bubblesort(int *a, int sz) {
  int i, j, tmp;
  for (i=0; i<sz; i++) {
    for (j=0; j<sz-1; j++) {
      if (a[j] > a[j+1]) {
	tmp = a[j];
	a[j] = a[j+1];
	a[j+1] = tmp;
      }
    }
  }
}

/* recursive binary search implementation
 * takes a sorted array a of size sz, and value v
 * returns -1 if v is not in a[0..sz-1], else returns
 * the index x at which a[x] == v
 */
int binsearch_r(int *a, int v, int sz) {
  int tmp;
  if (sz == 0) return -1;
  if (a[sz/2] == v) return sz/2;
  if (a[sz/2] < v) {
    tmp = binsearch_r(a+sz/2+1, v, sz-sz/2-1);
    if (tmp == -1) return -1;
    return sz/2+1+tmp;
  } else {
    /* why sz/2? because there are sz/2 elements to the left of a[sz/2]
     */
    return binsearch_r(a, v, sz/2);
  }
}

/* 0th fibonacci number is 0
 * 1st fibonacci number is 1
 * nth fibonacci number is the n-1st fibonacci number + n-2nd fibonacci number
 */
int fib(unsigned int n) {
  if (n <= 1) return n;
  return fib(n-1)+fib(n-2);
}

/* quicksort -- sorts an array a of size sz in increasing order
 *   base case: traditionally, 1 element or empty array
 *              practically, ~10 elements, run insertion sort
 *   step 1: choose a pivot (first element of the array <- NOT OPTIMAL)
 *   step 2: arrange the array so that the left side
 *           has elements <= pivot
 *           right side has elements >= pivot
 *           in between the two sides is the pivot
 *   step 3: recursively sort the left and right sides
 */
void quicksort(int *a, int sz) {
  int pivot, left, right, tmp;
  /* base case */
  if (sz <= 1)
    return;

  pivot = a[0];
  left = 1;
  right = sz-1;
  while (left < right) {
    /* move left to the right until we find something on the left that should
     * be on the right
     */
    while ((left < right) && (a[left] <= pivot)) left++;

    /* move right to the left until we find something on the right
     * that should be on the left
     */
    while ((left < right) && (a[right] >= pivot)) right--;

    tmp = a[left];
    a[left] = a[right];
    a[right] = tmp;
  }
  /* assert(a[left] > pivot)
   * can fail if all of the elements are less than the pivot
   * and the first time through the outer while,
   * the for loop went to the very end and became equal to right
   */
  if (a[left] < pivot) {
    print_array(a, sz);
    printf("%d %d\n", left, right);
    assert(0);
  }

  a[0] = a[left-1];
  a[left-1] = pivot;

  quicksort(a, left-1);
  quicksort(a+left, sz-left-1);
}

/* insertion sort: iterate through the array sz times
 * The i-th time (1-indexed) through the array,
 * the goal is to have the first i elements of the array
 * unchanged, but in sorted order
 */
void insertsort(int *a, int sz) {
  int i, j, k, tmp;
  for (i=1; i<sz; i++) {
    /* PRE: a[0..(i-1)] is sorted
     * POST: put a[i] into the right place within the subarray
     * a[0..i]
     * Example: i == 2, a[] = {167 241 217}, eventually want
     * a[] = {167,217,241}
     */
    for (j=0; j<i; j++)
      if (a[i] < a[j])
	break;
    /* at this point, a[j..(i-1)] is "misplaced" before a[i] */
    tmp = a[i];
    for (k=i; k>j; k--)
      a[k] = a[k-1];
    a[j] = tmp;
  }
}

void print_array(int *a, int sz) {
  int i;
  for (i=0; i<sz; i++) printf("%d ", a[i]);
  printf("\n");
}

#define SZ 16

int main() {
  int arr[SZ];
  int x, i;
  srand(getpid());
  for (i=0; i<SZ; i++)
    arr[i] = rand() & 0xff;
  print_array(arr, SZ);
  /*insertsort(arr, SZ);*/
  quicksort(arr,SZ);
  print_array(arr, SZ);

  return 0;
  while (1) {
    scanf("%d", &x);
    printf("%d\n", fib(x));
    /* printf("%d\n", binsearch_r(arr, x, SZ)); */
  }
  return 0;
}
