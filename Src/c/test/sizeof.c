// sizeof.c 
// uses c99 %z modifier
#define _POSIX
#include <stdio.h>
int
main(int argc, char *argv[])
{
   int n = 0;
   size_t intsize;
   
   intsize = sizeof(int);
   printf("n = %d, n has %zu byes; all ints have %zu bytes.\n", n, sizeof n, intsize);
   
   return 0;
}