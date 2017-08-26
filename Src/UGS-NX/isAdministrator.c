/*-------------------------------------------- isAdministrator.c -----
 | Function: isAdministrator(int required)
 | Author  : william h robertson
 | 
 | Purpose : See if running as administrator
 | Params  : required: Either true or false (1 or 0)
 | Returns : void
 | Usage   : isAdministrator(true);
 | Requires: <stdio.h>                 errorExit(Msg)
 | Notes   : Function tries to create 'test.txt' in a system dir.
 |           If succesful, it deletes the file on exit.
 | --Ver--  ---Date---  ----By----  --- Description of the Change ---
 |     0    07-20-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <stdio.h>
#define  true   1
#define  false  0            // Not used, just here for looks

void errorExit(char *msg); 

void
isAdministrator(int required)
{
   FILE *out = NULL;
   char *tmp = "c:/Program Files/test.txt";

   // if Admin Required, check if we are running as Administrator
   if(required && ( out = fopen(tmp, "wb") ) == NULL)
		errorExit("Error: Program must be run as an Administrator.");

   if(out){
      fclose(out);
      remove(tmp);   
   }
}
