#include <strings.h>
/*----------------------------------------------------------- StrLib.c
 | Function: ltrim, rtrim or trim(char *str)
 | Author  : william h robertson
 |
 | Purpose : Remove ctrl chars & spaces from head &/or tail of string
 |
 | Params  : str-address  (string to remove chars from)
 |
 | Returns : str-address   (string can't be const string)
 |
 | Usage   : str = rtrim(char *str) or
 |           str = ltrim(char *str) or
 |           str =  trim(char *str)
 |
 | Requires: <strings.h>
 |
 | Notes   : Can't call function like: ltrim("   string"), because
 |           this is a const string & it will cause pgm to abort.
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     1    08-22-2017      whr     Initial release
 |
 *------------------------------------------------------------------*/

#if defined TEST
#include <stdio.h>
#endif

/* ---------------------------------------------------------
   Remove leading white space & ctrl chars from string.
*/
char *ltrim(char *str)
{
   char *obuf;

   if (str)
   {
      for (obuf = str; *obuf && (*obuf <= ' '); ++obuf)
                ;       // For loop does it all!
      if (str != obuf)
         memmove(str, obuf, strlen(obuf)+1);
   }

   return str;
}


/* ---------------------------------------------------------
   Remove trailing white space & cntrl chars from string.
*/

char *rtrim(char *str)
{
    int n;

    if (str)            // Do nothing if str is NULL
    {
        for( (n = strlen(str)); str[n] <= ' '; n-- )
            ;           // For loop does it all

        str[++n] = '\0';
    }

    return str;
}


/* ---------------------------------------------------------
   Remove leading & trailing white space & cntrl chars.
*/
char *trim(char *s)
{
    return (rtrim(ltrim(s)));
}


/* ---------------------------------------------------------
   Simply test to see if routines work at least sometimes.
*/
#if defined TEST
int
main()
{
   char str_1[] = "\tThis is a string with tabs, spaces & new lines        \n";
   char str_2[] = "\tThis is also a string with tabs, spaces & new lines   \n";

   printf("Length of the string 1:%3d\n", strlen(str_1));
   printf("Length of the string 2:%3d\n", strlen(str_2));

   printf("1st string untrimmed: <%s>\n", str_1);
   printf("1st String rtrimmed : <%s>\n", rtrim(str_1));
   printf("1st String ltrimmed : <%s>\n", ltrim(str_1));

   printf("\n");
   printf("2nd string untrimmed: <%s>\n", str_2);
   ltrim(str_2);
   printf("2nd String ltrimmed : <%s>\n", str_2);
   rtrim(str_2);
   printf("2nd String rtrimmed : <%s>\n", str_2);

   return 0;
}
#endif
