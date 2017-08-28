#include <string.h>
#include <ctype.h>
/*----------------------------------------------------- SpacesBefore.c
 | Function: size_t SpacesBefore(const char *string)
 | Author  : william h robertson
 |
 | Purpose : Get number of leading spaces in a string.
 |
 | Params  : *string (to parse)
 |
 | Returns : number of leading spaces (of size_t)
 |
 | Usage   : nSpacesBefore = SpacesBefore( *str);
 |
 | Notes   : Conforms to SEI CERT C Coding Standard, 2016 Edition
 |           for secure coding in the C programming language.
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    08-22-2012      whr     Initial release
 |     1    08-21-2017      whr     Updated to conform to SEI CERT C
 |                                  Conding Standard, 2016 Edition
 *------------------------------------------------------------------*/

int
SpacesBefore(const char *s)
{
   const char *t = s;
   int length = strlen(s) + 1;

   while(isspace( (unsigned char) *t) && (t-s < length)){
      ++t;
   }

   return t - s;
}
