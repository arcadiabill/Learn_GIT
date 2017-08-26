/* Print program arguments and enviroment parameters */
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[], char *envp[])
{
   int i;
   
   printf("Program Name: %s\n\n", argv[0]);
   
   // Print any parameters passed
   printf("Number Passed Parameters: %d", argc);
   
   for(i=1; argv[i]; i++)
   {
      printf("%2d: %s\n", i, argv[i]);
   }
   
   // Print environment variables
   for(i=0; envp[i]; i++)
   {
      printf("%2d: %s\n", i, envp[i]);
   }
   
   return 0;
}