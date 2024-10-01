#include <stdio.h>

/* compare strings in case-sensitive dictionary order
 * returns 0 if a and b are lexically the same
 * returns a negative value if a is lexically before b
 * returns a positive value if a is lexically after b
 */
int stringcmp(const char *a, const char *b) {
  while (*a || *b) {
    /* if (*(a++) != *(b++)) return *(--a)-*(--b); */
    if (*a < *b) return -1;
    if (*a > *b) return 1;
    a++;
    b++;
  }

  /*
  for (; *a || *b; a++, b++)
    if (*a != *b) return *a-*b;
  */
  
  return 0;
}

/* returns the number of non-NUL characters in the nul-terminated string str
 */
unsigned int stringlen(const char *str) {
  unsigned int i = 0;
  while (*str) {
    i++; str++;
  }
  return i;
}

/* copies the string held by src into the location specified by dst */
void stringcpy(char *dst, const char *src) {
  unsigned int len = stringlen(src)+1;
  int i;
  if ((dst > src) && (len >= (dst-src))) {
    /* do the copy back to front */
    for (i=len-1; i>=0; i--)
      dst[i] = src[i]; /* *(dst+i) = *(src+i); */
  } else {
    src--;
    do {
      *(dst++) = *(++src);
    } while (*src);
  }
  /*
  do {
    *(dst++) = *(src++);
  } while (src[-1]);

  do {
    *(dst++) = *src;
  } while (*(src++));
  */
}

/* read input from stdin until we get a \n and put that string into
 * str
 */
void read_string(char *str, int len) {
  do {
    scanf("%c", str);
    len--;
  } while (len && *(str++) != '\n');
  str[-1] = '\0';
}

int main(int argc, char **argv) {
  char str[16] = "abc";
  read_string(str,16);
  printf("%s\n", str);
  /*
  stringcpy(str+1, str);
  printf("%s\n", str);
  */
  return 0;
  /*
  if (argc < 3) {
    printf("Try again.\n");
    return 1;
  }
  printf("%s %s %d\n", argv[1], argv[2], stringcmp(argv[1], argv[2]));
  return 0;
  */
}
