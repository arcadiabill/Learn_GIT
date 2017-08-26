/*--------------------------------------------------- fixPaths.c -----
 | Function: fixPaths(char *sourcePath, char *destPath)
 | Author  : william h robertson
 |
 | Purpose : Check & fix any errors found in the paths. Exit progam if
 |           it's not possible to fix the path
 | Params  : sourcePath: Path of the installation media
 |           destPath  : Path the program is installed on
 |                       Probably c:\Prgram Files\Siemens\NX 10.0 ...
 | Returns : Nothing, ABORTS if it can't fix the errors
 | Usage   : fixPaths(sourcePath, destPath);
 | Requires: <string.h>                errorExit(msg)
 |           addPathSprtr(Line)        trimLine(Line)
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    07-20-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <string.h>

int  addPathSprtr(char *Line);
void errorExit(char *msg);
int  trimLine(char *Line);

void
fixPaths(char *sourcePath, char *destPath)
{
   // First make sure c: drive isn't a source drive
   if( strncasecmp(sourcePath, "c:", 2) == 0)
      errorExit("Error: Source path can't be the system's drive\n");

   trimLine(sourcePath);
   trimLine(destPath);
   addPathSprtr(sourcePath);
   addPathSprtr(destPath);
}
