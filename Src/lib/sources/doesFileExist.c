/*---------------------------------------------------- doesFileExist.c
 | Function: doesFileExist(const char* filename)
 | Author  : william h robertson
 |
 | Purpose : See if file exists without opening the file.
 |
 | Params  : Filename of the file
 |
 | Returns : 0 of file exists or 1 if file does not exist
 |
 | Usage   : doesFileExist(fileName);
 |
 | Requires: <sys/stat.h>
 |           <error.h>
 |
 | Notes   : Function limited to 32-bit filesize (around 4GB)
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     1    09-22-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <sys/stat.h>
#include <errno.h>

long unsigned
doesFileExist(const char* filename)
{
    struct stat st;

    errno = 0;
    if(stat(filename, &st) != 0) {
        return 1;  //for Cmd line parameter
    }

    return 0;
}
