// crt_stat.c
// This program uses the _stat function to
// report information about the file named crt_stat.c.

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
void modes(int, char str[]);

int main( void )
{
   struct _stat buf;
   int result;
   char timebuf[26];
   char* filename = "crt_stat.c";
   errno_t err;
   char str[] = "rrrrrrrrr";

   // Get data associated with "crt_stat.c":
   result = _stat( filename, &buf );

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
	  modes( buf.st_mode, str);
      printf( "File size     : %ld\n", buf.st_size );
      printf( "Drive         : %c:\n", buf.st_dev + 'A' );
	  printf( "Modes         : %s:\n", str );
      err = ctime_s(timebuf, 26, &buf.st_mtime);
      if (err)
      {
         printf("Invalid arguments to ctime_s.");
         exit(1);
      }
      printf( "Time modified : %s", timebuf );
	  ctime_s(timebuf, 26, &buf.st_atime);
	  printf( "Time accessed : %s", timebuf );
	  ctime_s(timebuf, 26, &buf.st_ctime);
	  printf( "Time created  : %s", timebuf );
   }
}

void
modes(int mode, char str[] )
{
   if ( mode & S_IRUSR ) str[1] = 'r';    /* 3 bits for user  */
   if ( mode & S_IWUSR ) str[2] = 'w';
   if ( mode & S_IXUSR ) str[3] = 'x'; 

   if ( mode & S_IRGRP ) str[4] = 'r';    /* 3 bits for group */
   if ( mode & S_IWGRP ) str[5] = 'w';
   if ( mode & S_IXGRP ) str[6] = 'x';

   if ( mode & S_IROTH ) str[7] = 'r';    /* 3 bits for other */
   if ( mode & S_IWOTH ) str[8] = 'w';
   if ( mode & S_IXOTH ) str[9] = 'x';
   return;
}
