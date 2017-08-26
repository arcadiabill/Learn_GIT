// What: fast power mod.
#include <stdio.h>
#include <stdlib.h>

int modular_pow(int b, int p, int n){
  int r = 1;
  while (p > 0) {
    if (p % 2 == 1) {
      r = (r * b) % n;
    }
    p = p >> 1;
    b = (b * b) % n;
  }
  // Return: b^p mod n, complexity O(lg(p))
  return r;
}

int main() {
  int b, p = 2, n = 100;
  for(b=0;b<=10;b++){
    printf("%d^%d mod 100 = %d\n", b, p, modular_pow(b,p,n));
  }
  b = 2;
  for(p=0;p<=10;p++){
    printf("%d^%d mod 100 = %d\n", b, p, modular_pow(b,p,n));
  }
  return 0;
}
