#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct StudentStruct
{
	char *Name;
	int UIN;
	float GPA;
} student;

int main() {
  int i, j;
  student *arr = malloc(200*sizeof(student));
  const char *str = "To be set";
  //char whatever[100] = "To be set";
  for (i=0; i<200; i++) {
    /* instantiate Name to be a new array of 100 characters */
    arr[i].Name = malloc(100*sizeof(char));
    /* Initialize name to "To be set", UIN to -1 and GPA to 0.0 */
    arr[i].UIN = -1;
    arr[i].GPA = 0.0;
    for (j=0; j<=strlen(str); j++) {
      arr[i].Name[j] = str[j];
    }
  }
  for (i=0; i<200; i++) {
    free(arr[i].Name);
  }
  free(arr);
}
