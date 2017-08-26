// crt_stat.c
// This program uses the _stat function to
// report information about the file named TestNumber.exe.

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main( void )
{
   struct stat buf;
   int result;
//   char timebuf[26];
   char* filename = "statFile.exe";

   // Get data associated with "TestNumber.exe": 
   result = stat( filename, &buf );

   // Check if statistics are valid: 
   if( result != 0 )
   {
      perror( "Problem getting information" );
      switch (errno)
      {
         case ENOENT:
           printf("File %s not found.\n", filename);
           break;
         case EINVAL:
           printf("Invalid parameter to _stat.\n");
           break;
         default:
           /* Should never be reached. */
           printf("Unexpected error in _stat.\n");
      }
   }
   else
   {
      // Output some of the statistics: 
      printf( "File size     : %ld\n", buf.st_size );
      printf( "Drive         : %c:\n", buf.st_dev + 'A' );
	  
	  printf("aTime %ld\n", buf.st_atime);
	  printf("mTime %ld\n", buf.st_mtime);
	  printf("cTime %ld\n", buf.st_ctime);
   }
}
