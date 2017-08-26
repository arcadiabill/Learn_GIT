/*-------------------------------------------------- errorExit.c -----
 | Function: errorExit(char *msg)
 | Author  : william h robertson
 |
 | Purpose : Write a mesage to stderr & exit program
 | Params  : msg: The message to show on the screen
 | Returns : void
 | Usage   : errorExit(msg)
 | Requires: <stdio.h>
 |           <stdlib.h>
 | Notes   : 
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    07-20-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

 void
 errorExit(char *msg)
 {
    fprintf(stderr, msg);
    fprintf(stderr, "\nPress [Enter] key to return to the OS");
    getchar();
    exit(EXIT_FAILURE);
 }
