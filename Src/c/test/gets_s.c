#include <stdio.h>
#include <string.h>

int
main(void)
{
   char test[50];
   
   puts("INput a string: ");
   gets_s(test, 50);
   printf("String: <%s>");
   
   return 0;
}