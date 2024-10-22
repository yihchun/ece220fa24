#include <stdio.h>
#include <string.h>
typedef struct StudentStruct
{
	char Name[100];
	int UIN;
	float GPA;
} student;

float average_gpa(student *s, int len) {
  float tot = 0;
  int i;
  for (i=0; i<len; i++)
    tot += s[i].GPA;
  return tot/len;
}

void test() {
  student ece220[400];

  printf("%s %d %f\n", ece220[0].Name, ece220[0].UIN, ece220[0].GPA);

  //access individual fields in each element
  ece220[0].Name[0] = 'J';
  ece220[0].Name[1] = 'o';
  ece220[0].Name[2] = 'h';
  ece220[0].Name[3] = 'n';
  ece220[0].Name[4] = '\0';
  ece220[0].UIN = 123456789;
  ece220[0].GPA = 3.89;

  strncpy(ece220[1].Name, "Jane Doe", 100);
  ece220[1].UIN = 987654321;
  ece220[1].GPA = 4.00;
  printf("%f\n", average_gpa(ece220, 2));

  printf("%s %d %f\n", ece220[0].Name, ece220[0].UIN, ece220[0].GPA);
}

void foo() {
  int a[1000];
  int i;
  for (i=0; i<1000; i++)
    a[i] = 0xabcdef12 - i;
  return;
}

int main() {
  printf("This is a test of our structures\n");
  foo();
  test();
  return 0;
}
