/*------------------------------------------------------- FileExists.c
 | Function: FileExists(const char* filename)
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
 | Usage   : FileExists(fileName);
 |
 | Requires: <sys/stat.h>
 |           <error.h>       for global error varable
 |
 | Notes   : 1. Function limited to 32-bit filesize (around 2GB)
 |              even though it's not trying to get the filesize.
 |           2. Same code as doesFileExist(const char* filename)
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     1    08-24-2017      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <sys/stat.h>
#include <errno.h>           // for global errno

#define true  1
#define false 0

int
FileExists(const char *filename)
{
   struct stat st;

   errno = 0;               // Set global error var to 0
   if(stat(filename, &st) != 0) {
      return false;
   }

   return true;
}
