#include <stdio.h>

#define BUFSZ 256
int main() {
  /* invert the image in a.pnm and output it to b.pnm */
  FILE *in, *out;
  int w, h, d, r;
  char buf[BUFSZ];
  in = fopen("a.pnm", "r");
  out = fopen("b.pnm", "w");
  
  fgets(buf, BUFSZ, in); /* read P6 */
  fscanf(in, "%d %d", &w, &h); /* read width and height */
  fscanf(in, "%d", &d); /* read depth */

  /* read characters until the newline */
  while ((r = fgetc(in)) != '\n')
    ;
  
  fprintf(out, "P6\n%d %d\n%d\n", w, h, d);

  while ((r = fgetc(in)) != EOF)
    fputc(d-r, out);

  fclose(in);
  fclose(out);
  return 0;
}
  
