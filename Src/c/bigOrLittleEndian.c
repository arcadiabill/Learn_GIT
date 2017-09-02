#include <stdio.h>
/* Check if computer uses little or big endian for memory storage */
union Udouble {
   double d;
   unsigned char c[8];
};

int main()
{
   union Udouble u;

   printf("\nChecking if computer uses big or little endian memory addressing\n\n");

   u.d = 6.5;
   for (int i=7; i>=0; i--) printf("%02x", u.c[i]);
   if(u.c[7] == 64) {
      printf("\n\nIt uses little endian: %02x -- big endian would print : %02x\n", u.c[7], u.c[6]);
   } else {
      printf("\n\nIt uses big endian: \%02x -- little endian would print : %02x\n", u.c[7], u.c[6]);
   }

   return 0;
}
