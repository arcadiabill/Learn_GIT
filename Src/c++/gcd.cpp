#include <iostream>
#include <algorithm>
using namespace std;

int main()
{  int a,b;
   a = 9172;
   b = 92;
   cout << "gcd of " << a << " and " << b << "is: " ;
   while(a %= b)swap(a,b);
   
   cout << b << "\n";
}
