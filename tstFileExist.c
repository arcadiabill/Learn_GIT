#include <stdio.h>
#include <errno.h>

/* Test function FieExists()
 *
 * Compile using:
 *   gcc -static tstFileExist.c -std=c11 -L\src\lib -libwhr.a -otstFileExist
 */
unsigned int FileExists( const char *filename);

int
main(int argc, char *argv[])
{
   if(argc < 2){
      puts("Usage: tstFile filename");
      return 1;
   }
   
   if(FileExists(argv[1])){
      perror("");
   }
   else{
      perror("Error");
   }
   
   return 0;
}
   