#include <iostream>
#include <limits>

using namespace std;

int main()
{
	cout << "Limits lDbl: " << numeric_limits<long double>::digits10 << endl;
	cout << "Limits Dbl : " << numeric_limits<double>::digits10 << endl;
   cout << "Long       : " << sizeof(long) << endl;
   cout << "Short      : " << sizeof(short) << endl;
   cout << "Double     : " << sizeof(double) << endl;
   cout << "Long Long  : " << sizeof(long long) << endl;
   cout << "Long Double: " << sizeof(long double) << endl;
	return 0;
}
