/*---------------------------------------------------- doesFileExist.c
 | Function: doesFileExist(const char* filename)
 | Author  : william h robertson
 |
 | Purpose : See if file exists without opening the file.
 |
 | Params  : Filename of the file
 |
 | Returns : 1 if file exists or 0 if file does not exist. It also
 |           returns global variable errno. If there was an error,
 |           errno will be set to a non-zero value.
 |
 | Usage   : doesFileExist(fileName);
 |
 | Requires: <sys/stat.h>
 |           <error.h>
 |
 | Notes   : 1. Function limited to 32-bit filesize (around 2GB)
 |              even though it's not trying to get the filesize
 |           2. Same code as FileExists(const char* filename)
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     1    09-22-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <sys/stat.h>
#include <errno.h>                  // For global errno

#define TRUE  1
#define FALSE 0

int
doesFileExist(const char* filename)
{
   struct stat st;

   errno = 0;
   if(stat(filename, &st) != 0) {  // errno set if you need to
      return FALSE;                 // see why this failed
   }

   return TRUE;
}
