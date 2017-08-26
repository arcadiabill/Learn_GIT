// from gmp man page
// Usage: gcc -o gmp-usage.exe gmp-usage.c -lgmp
// 2012-Dec-20 Thu 19:56
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
 
int main(void) {
  mpz_t x, y, x_into_y;
  
  mpz_init(x);
  mpz_init(y);
  mpz_init(x_into_y);
  
  mpz_set_str(x, "7612058254738945", 10);
  mpz_set_str(y, "9263591128439081", 10);
  
  mpz_mul(x_into_y, x, y);
  gmp_printf("  %Zd\n* %Zd\n= %Zd\n", x, y, x_into_y);
  
  mpz_clear(x);
  mpz_clear(y);
  mpz_clear(x_into_y);
  return EXIT_SUCCESS;
}
