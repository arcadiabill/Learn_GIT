#include <stdio.h>
unsigned long getFilesize(const char* filename);

int
main(int argc, char *argv[])
{
   if(argc < 2)
   {
      puts("Could not find input file.");
      return -1;
   }
   
   printf("%s: Size: %lu\n", argv[1], getFilesize(argv[1]));
   
   return 0;
}