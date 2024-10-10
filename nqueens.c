#include <stdio.h>

/* board is an nxn array
 * PRE: board does not contain any pair of queens that see each other.
 * returns 1 and populates board with 1s where queens are
 *   and 0s where queens aren't if the board state is solvable
 * returns 0 and does not modify board
 */
int nqueens(int *board, unsigned int n) {
  int r, c, i, j;
  /* find an empty row */
  for (r=0; r<n; r++) {
    for (c=0; c<n; c++) {
      if (board[r*n+c]) break;
    }
    if (c == n) break;
  }
  if (r == n) return 1;
  /* place a queen on each col of that row*/
  for (c=0; c<n; c++) {
    /* check if column c is empty */
    for (i=0; i<n; i++)
      if (board[n*i+c])
	break;
    if (i<n) continue; /* there is a queen in col c */
    /* check if all 4 half-diags are empty */
    for (i=1; i<n; i++) {
      if ((r >= i) && (c >= i) && board[(r-i)*n+(c-i)]) break; /* up and left A && B && ...*/
      if ((r+i < n) && (c+i < n) && board[(r+i)*n+(c+i)]) break; /* down and right C && D & .. */
      if ((r >= i) && (c+i < n) && board[(r-i)*n+(c+i)]) break; /* up and right */
      if ((r+i < n) && (c >= i) && board[(r+i)*n+(c-i)]) break; /* down and left */
    }
    if (i<n) continue; /* there is a queen on one of the diags */
    board[r*n+c] = 1;
    if (nqueens(board, n)) return 1;
    board[r*n+c] = 0;
  }
  /* if we can't place one, then fail */
  return 0;
}

void print_board(const int *board, int n) {
  int i,j;
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++)
      printf("%c", board[i*n+j] ? 'Q':'-');
    printf("\n");
  }
}

#define N 8
int b[N][N];

int main() {
  nqueens(b[0], N);
  print_board(b[0], N);
  return 0;
}

