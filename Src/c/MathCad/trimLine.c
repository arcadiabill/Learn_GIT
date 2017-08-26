/*--------------------------------------------------- trimLine.c -----
 | Function: trimLine(char *Line)
 | Author  : william h robertson
 |
 | Purpose : Remove trailing chars <= space char from the end
 | Params  : Line to trim
 | Returns : nLength - The new string length
 | Usage   : nLength = trimLine(Line);
 | Requires: <string.h>
 | Notes   : 
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    07-20-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <string.h>

int
trimLine(char *Line)
{
   int nPos = strlen(Line) - 1;        // Position of last char
   
   if(nPos < 0) return 0;
   
   while(Line[nPos] <= ' ')
   {
      Line[nPos] = '\0';

      --nPos;
      if(nPos < 0) return 0;
   }
   
   return ++nPos;            // Length is 1 more for the '\0'
}
