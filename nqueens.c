#include <stdio.h>

/* board is an nxn array
 * returns 1 and populates board with 1s where queens are
 *   and 0s where queens aren't if the board state is solvable
 * returns 0 and does not modify board
 */
int nqueens(int *board, unsigned int n) {
  int r, c;
  /* find an empty row
   * place a queen on each col of that row
   * recursive call
   */
  for (r=0; r<n; r++) {
    for (c=0; c<n; c++) {
      if (board[r*n+c])
	break;
    }
    if (c == n)
      break;
  }
  /* r is an empty row */
  for (c=0; c<n; c++) {
    board[r*n+c] = 1;
    if (nqueens(board, n))
      return 1;
    board[r*n+c] = 0;

      
    
  
}

