#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct word_s {
  char *text;
  int count;
} word;

word *word_search(word *dict, int count, const char *lookup) {
  int i;
  for (i=0; i<count; i++)
    if (!strcmp(dict[i].text, lookup))
      return dict+i;
  return NULL;
}

int main() {
  FILE *fp = fopen("hamlet.txt", "r");
  char buf[256];
  int i, count = 0, capacity = 16;
  word *dict = malloc(sizeof(word) * capacity);
  word *ret;
  char *token;
  /* allocate some word and text space */
  /* start with 0 words */

#define SEP " \r\n-.!?,;[]:()"
  while (fgets(buf, sizeof(buf), fp)) {
    for (token = strtok(buf, SEP);token;token = strtok(NULL, SEP)) {
      if (!strlen(token)) continue;
      /* if this a new word, use one more word
       * if there are no more words, double size
       */
      ret = word_search(dict, count, token);
      if (!ret) {
	if (count == capacity) {
	  dict = realloc(dict, capacity*2*sizeof(word));
	  if (!dict) return -1;
	  capacity *= 2;
	}
	dict[count].text = malloc(sizeof(char)*(strlen(token)+1));
	strcpy(dict[count].text, token);
	dict[count].count = 1;
	count++;
      } else {
	ret->count++;
      }
    }
  }

  for (i=0; i<count; i++) {
    printf("%s %d\n", dict[i].text, dict[i].count);
    free(dict[i].text);
  }
  free(dict);
  fclose(fp);
}
