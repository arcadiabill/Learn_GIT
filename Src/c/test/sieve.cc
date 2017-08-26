#include <iostream>
#include <vector>
void write_number(int n)
{
   std::cout << " " << n;
}

int sieve(int n)
{
   static int nPrimes = 0;
   std::vector<bool> is_prime(n + 1, true); // Initializes variables

   for (int i = 2; i <= n; ++i) {
      if (is_prime[i]) {
         ++nPrimes;
         write_number(i);
         for (int j = i; j <= n / i; ++j) {
            is_prime[i * j] = false;
         }
      }
   }
   return nPrimes;
}

int get_input()
{
   int n;
   std::cout << "This program lists all primes up to a given integer.\n"
             << "Enter an integer: ";
   std::cin >> n;
   return n;
}

int main()
{
   int nPrimes;
   int n = get_input();
   if (n < 2) {
      std::cout << "There are no primes less than 2.\n";
   }
   else {
      std::cout << "The primes up to " << n << " are:";
      nPrimes = sieve(n);
      std::cout << ".\n";
      std::cout << "There were " << nPrimes << " of them.\n";
   }
}
