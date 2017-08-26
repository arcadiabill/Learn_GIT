// From http://en.wikipedia.org/wiki/GNU_Multiple_Precision_Arithmetic_Library
// Date: 2013-03-29 

#include <iostream>
#include <gmpxx.h>
 
int main() {
  mpz_class x("7612058254738945");
  mpz_class y("9263591128439081");
 
  std::cout << "\n    " << x << "\n    *  \n    " << y;
  std::cout << "\n--------------------\n" << x * y << "\n";
}
