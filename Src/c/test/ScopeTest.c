#include <stdio.h>
#include <string.h>

int
main(void)
{
   int nCounter = 0;
   
   do {
      static int nCounter = 0;
      
      nCounter += 3;
      printf("nCounter is: %d\n", nCounter);
   } while( ++nCounter < 10);
   
   printf("Ended: nCounter is: %d\n", nCounter);
}
