#include <stdio.h>

/* This function takes a n*n x n*n sudoku board that is valid
 * (meaning that the same non-zero number does not occur in any row, column,
 * or n*n sub-cell) except it may contain some 0s indicating a blank space.
 * It either
 *   a) if the board is unsolvable, returns 0 with the board unchanged, or
 *   b) if the board is solvable, returns 1 with the board set to one such
 *      solution
 */
int solve_sudoku(int *board, int n) {
  int i, j, k, l, a, b, r, c;
  for (i=0; i<n*n*n*n; i++)
    if (!board[i])
      break;
  r = i/(n*n);
  c = i%(n*n);
  if (i==n*n*n*n) return 1;
  for (i=1; i<=(n*n); i++) {
    for (j=0; j<(n*n); j++) {
      if (board[r*n*n+j] == i) break; /* check row */
      if (board[j*n*n+c] == i) break; /* check col */
      a = r-r%n;
      b = c-c%n;
      k = j/n;
      l = j%n;
      if (board[(a+k)*n*n+(b+l)] == i) break; /* check sub-cell */
    }
    if (j<(n*n)) continue;
    /* i is valid at location r,c */
    board[r*n*n+c] = i;
    if (solve_sudoku(board, n)) return 1;
    board[r*n*n+c] = 0;
  }
  return 0;
}

void print_board(const int *board, int n) {
  int i,j;
  for (i=0; i<(n*n); i++) {
    for (j=0; j<(n*n); j++) {
      printf("%2d", board[i*n*n+j]);
    }
    printf("\n");
  }
}

#define N 3
int board[N*N][N*N] = {8,1,5,0,0,4,0,7,0,2,9,0,0,0,0,1,0,0,3,4,7,1,0,2,0,6,0,9,0,0,3,0,6,2,5,0,0,6,0,0,2,7,0,3,9,7,2,0,0,0,9,8,1,0,1,0,9,4,6,0,5,2,3,4,0,0,2,0,3,0,0,1,0,0,0,9,5,1,0,8,0};

int main() {
  solve_sudoku(board, N);
  print_board(board, N);
}
