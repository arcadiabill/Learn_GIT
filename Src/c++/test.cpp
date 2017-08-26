#include <iostream>
using namespace std;

int main()
{
    int x = 5;
    int *p_x = &x;
    cout << "x is currently " << x << endl;
    *p_x = 2;
    cout << "x is now " << x << endl;
    
    return 0;
}
