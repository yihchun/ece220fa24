#include <stdio.h>
int main() {
	FILE *in_file;
	FILE *out_file;
	int m, n, i, j;

	in_file = fopen("in_matrix.txt", "r");
	if (in_file == NULL)
		return -1;

	fscanf(in_file, "%d %d", &m, &n);
	int matrix[m][n];

	out_file = fopen("out_matrix.txt", "w");
	if (out_file == NULL)
		return -1;

	fprintf(out_file, "%d %d\n", n, m); 

	/* Read the matrix from the input file */
	for (i=0; i<m; i++)
	  for (j=0; j<n; j++)
	    fscanf(in_file, "%d", &matrix[i][j]);

	for (i=0; i<n; i++) {
	  for (j=0; j<m; j++)
	    fprintf(out_file, "%d ", matrix[j][i]);
	  fprintf(out_file, "\n");
	}

	fclose(in_file);
	fclose(out_file);

	return 0;
	
}
