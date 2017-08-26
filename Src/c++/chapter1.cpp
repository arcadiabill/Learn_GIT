// Chapter1.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char* argv[])
{
    cout << "What is your name? ";
    string name {};
    cin >> name;
    cout << "You said your name is: " << name << endl;
    return 0;
}
