/*------------------------------------------------ getFilesize.c -----
 | Function: getFilesize(const char *filename)
 | Author  : william h robertson
 | Purpose : Get filesize of passed filename without opening the file.
 |
 | Params  : Filename of the file
 | Returns : Filesize (long unsigned)
 | Usage   : fileSize = getFilesize( fileName);
 | Requires: <sys/stat.h>
 | Notes   : Function limited to 32-bit filesize (around 4GB)
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    07-20-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <sys/stat.h>

long unsigned
getFilesize(const char *filename)
{
    struct stat st;

    if(stat(filename, &st) != 0) return 0;
    
    return st.st_size;   
}
