#include <stdio.h>

int
gcd(int u, int v)
{
   int t;
   
   while(u > 0)
   {
      if(u < v)
      {
         t = u;
         u = v;
         v = t;
      }
      u = u % v;
      printf("%8d", u);
   }
   return v;
}

int
main()
{
   int x,y;
   
   printf("GCD Rev 0\n\nCalculate the Greatest Common Divisor of two integers, ");
   printf("Ctrl-C to quit\n");
   printf("Input two integers:\n");
   while(scanf("%d %d", &x, &y) != EOF)
   {
      if(x > 0 && y > 0) printf("The GCD of %d %d is %d\n", x, y, gcd(x, y));
   }
}