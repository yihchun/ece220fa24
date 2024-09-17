#include <stdio.h>

int main(int argc, char **argv) {
  /* user will provide a, b, c, d
   * we will output a/b + c/d as a fraction
   */
  int a,b,c,d,gcd,num,den, large, small, tmp, flag;
  printf("Enter your values for a,b,c,d: ");
  scanf("%d%d%d%d", &a, &b, &c, &d);
  den = b*d;
  num = a*d+b*c;

  printf("Partial result: %d/%d\n", num, den);

  flag = 0;
  if (num < 0) { num = -num; flag++; }
  if (den < 0) { den = -den; flag++; }
  large = (num > den) ? num : den;
  small = (num < den) ? num : den;
  while ((large % small) > 0) {
    tmp = large;
    large = small;
    small = tmp % small;
  }

  gcd = small;

  num /= gcd;
  den /= gcd;
  
  /*  num%den */
  if (flag == 1) {
    printf("-");
  }
  if (num / den == 0) {
    printf("%d/%d\n", num%den, den);
  } else if (num % den == 0) {
    printf("%i\n", num/den);
  } else {
    printf("%i %d/%d\n", num/den, num%den, den);
  }
  return 0;
}
  
  /*
    switch illustration
    
  char c;
  const int tmp = argc;
  scanf("%c", &c);
  switch (c) {
  case '+': do_add(); break;
  case '-': do_sub(); break;
  case '*': do_mult(); break;
  case '/': do_div(); break;
  case '0': case '1': case '2': case '3': case '4': 
  case '5': case '6': case '7': case '8': case '9':
    push_stack(c-'0');
    break;
  case 49:
    
  case 'a'+3: case tmp:
  default:
    printf("I didn't know what to do with a %c\n", c);
  }
}

  */
