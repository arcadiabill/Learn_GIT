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
gcd2(int u, int v)
{
   while(v)
   {
      v ^= u ^= v ^= u %= v;
      printf("%8d", v);
   }
   return v;
}

int
main()
{
   int a = 461952;
   int b = 116298;
   
   gcd(a,b);
   printf("\n");
   gcd2(a,b);
   return 0;
}