#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int main(int argc, char *argv[])
{
   struct lconv *lc;

   system("chcp 65001");
   
   char *where = "en_US.UTF-8";
   setlocale(LC_MONETARY, where);
   lc = localeconv();
   printf("%s: %s %s\n", where, lc->currency_symbol, lc->int_curr_symbol);

   where = "en_AU.UTF-8";
   lc = localeconv();
   printf("%s: %s %s\n", where, lc->currency_symbol, lc->int_curr_symbol);

   where = "de_DE.UTF-8";
   lc = localeconv();
   printf("%s: %s %s\n", where, lc->currency_symbol, lc->int_curr_symbol);

   setlocale(LC_CTYPE, "");
   
   char *s = "€ © ♥"; 
   printf("%s\n", s);
   for (int k = 0; k < strlen(s); k++) printf("%02x ", (unsigned char)s[k]);
   printf("\nString Length: %d\n", strlen(s));
   
   return EXIT_SUCCESS;
}