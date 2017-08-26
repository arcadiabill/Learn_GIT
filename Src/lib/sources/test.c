// Test doesFileExist
// Used with compiled.cmd to test if a file exists
// No commands available in cmd library for this
#include <stdio.h>

long unsigned doesFileExist(const char* filename);

int main(int argc, char *argv[])
{
   int retValue = doesFileExist(argv[1]);

   if (argc > 2)
   {
      if(retValue == 0) printf("File: %s Exists.", argv[1]);
      else printf("File: %s Doesn't Exist.", argv[1]);
   }
   return retValue;
}
