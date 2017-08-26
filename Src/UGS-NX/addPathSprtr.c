/*----------------------------------------------  addPathSprtr.c -----
 | Function: addPathSprtr(char *Line)
 | Author  : william h robertson
 |
 | Purpose : If missing, put '\' on end
 | Params  : Line: The line to check
 | Returns : nLen - The new line length
 | Usage   : newLineLen = addPathSprtr(Line);
 | Requires: <string.h>
 | Notes   : Function does no error checking
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    07-20-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <string.h>

int
addPathSprtr(char *Line)
{
   int nLen = strlen(Line);
   
   if( !((Line[nLen-1] == '\\') || (Line[nLen-1] == '/')) ){
      Line[  nLen] = '\\';
      Line[++nLen] = '\0';
   }
   
   return nLen;
}
