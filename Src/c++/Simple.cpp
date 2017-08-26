#include <iostream>
// using namespace std;

int main()
{
   int sum = 0, valStart = -100, valEnd = 100;
   
   for (int val = valStart; val <= valEnd; ++val)
   {
      sum += val;
   }
   std::cout << "Sum of " << valStart << " through " << valEnd << " is " << sum << std::endl;
   return 0;
}
