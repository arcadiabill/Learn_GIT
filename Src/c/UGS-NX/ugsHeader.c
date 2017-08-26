 /*------------------------------------------------- ugsHeader.c -----
 | Function: ugsHeader(const char *PgmName)
 | Author  : william h robertson
 |
 | Purpose : Show program preamble & allow moving the terminal screen
 |           around & adjust it for better viewing
 | Params  : PgnName: Prgrogam name normally gotten from argv[0]
 | Returns : nothing
 | Usage   : ugsHeader(PgmName);
 | Requires: <stdio.h>
 |           <stdlib.h>
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    07-20-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

void
ugsHeader(char *PgmName)
{
	system("mode con: COLS=104 LINES=62");
	printf("\n  %s Version 1.0 2016-07-13\n\n", PgmName);

   printf(
    "    You can adjust the Font & Screen Size by clicking the little icon\n"
    "    in the upper left corner of this screen and selecting properties.\n"
    "    You can also move the screen around so that it's more comfortable.\n"
    "    I suggest changing the font to Lucidia Console and its size to 16.\n\n"
    "  Press [Enter] key when you are satisfied with the appearance.");
   getchar();
	system("cls()");
	printf("%s Version 1.0 2016-07-13\n\n", PgmName);
}
