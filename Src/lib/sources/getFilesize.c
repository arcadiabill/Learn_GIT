/*------------------------------------------------------ getFilesize.c
 | Function: getFilesize(const char* filename)
 | Author  : william h robertson
 |
 | Purpose : Get filesize of passed filename without opening the file.
 |
 | Params  : Filename of the file
 |
 | Returns : Filesize (long unsigned) or -1 on error
 |
 | Usage   : fileSize = getFilesize(fileName);
 |
 | Requires: <sys/stat.h>
 |           <error.h>
 |
 | Notes   : Function limited to 32-bit filesize (around 4GB)
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    07-20-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <sys/stat.h>
#include <errno.h>

long unsigned
getFilesize(const char* filename)
{
    struct stat st;

    errno = 0;
    if(stat(filename, &st) != 0) {
        return -1;
    }
    
    return st.st_size;   
}
