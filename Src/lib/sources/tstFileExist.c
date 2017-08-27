#include <stdio.h>
#include <errno.h>

/* Test function FieExists()
 *
 * Compile using:
 *   gcc -static tstFileExist.c -std=c11 -L\src\lib -lwhr -otstFileExist
 */
unsigned int FileExists( const char *filename);

int
main(int argc, char *argv[])
{
   if(argc < 2){
      fputs("Usage: tstFile filename", stderr);
      return 1;
   }
   
   if( ! FileExists(argv[1]))
      return 1;
   
   return 0;
}
   