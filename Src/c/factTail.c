#include <stdio.h>

int main(void)
{
  int n;
  
  n = 6;
  printf("The Factorial of %d is %d.", n, factTail(n, 1));
  return 0;
}

int factTail(int n, int a)
{
   if      (n <  0) return 0;
   else if (n == 0) return 1;
   else if (n == 1) return a;
   else return factTail(n-1, n*a);
}
