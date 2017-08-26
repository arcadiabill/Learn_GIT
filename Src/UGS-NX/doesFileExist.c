/*---------------------------------------------- doesFileExist.c -----
 | Function: doesFileExist(const char *filename)
 |
 | Author  : william h robertson
 | Purpose : See if the file exists without having to open it.
 |
 | Params  : filename: Name of the file to check for existance
 | Returns : true : The file exists
 |           false: The file doesn't exist or you don't have access
 | Usage   : bFileExists = doesFileExist(filename);
 | Requires: <sys/stat.h>
 | Notes   : Function checks to see if a file exists. It can return
 |           false if the file exists but you don't have access to it.
 |
 | --Ver--  ---Date---  ----By----  --- Description of the Change ---
 |     0    07-20-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
 #include <sys/stat.h>
 
 #define true  1
 #define false 0
 
int
doesFileExist(const char *filename)
{
   struct stat buffer;
   int    error = stat(filename, &buffer);

   if(error) return false;   // File Doesn't Exist
   else      return true ;  // File Does    Exist
}
