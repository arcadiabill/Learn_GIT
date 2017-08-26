#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

string FileName;



double Balance;


int main()
{
	cout << "Enter a file name (including extension): " << endl;
	char Checkbook[350];
	cin.getline (Checkbook,350);
	ifstream input(Checkbook);
	cout << "--------------------------------------------------------------------------" << endl;

	if (!input.good())
	{
		cerr << "Unable to open file " << Checkbook << " for reading."<< endl;
		exit(1);
	}
	while (!input.eof())
	{

		char Deposit[15];
		input.getline(Deposit, 15,':');
		cout << left << setw(21) << Deposit;
		
		char Date[20];
		input.getline(Date, 15, ':');
		cout << left << setw(15) << Date;

		char Location[20];
		input.getline(Location, 15, ':');
		cout << left << setw(15) << Location;

		cout << setw(15) << right <<"$" ;
			double Amount;
			ifstream input("checkbook.txt");
			cout.setf(ios::showpoint);
			cout.setf(ios::fixed);
			cout.precision(2);
			cout.width(8);		
		input.ignore();
    	cout << Amount << endl;
		
		if (Deposit[0] == 'd' || Deposit[1] == 'd' || Deposit[0] == 'D' || Deposit[1]== 'D')
		{
			Balance += Amount;
			
		}

		else
		{
			Balance -= Amount;
			
		}

	}

	cout <<endl << "--------------------------------------------------------------------------" << endl;
	cout << setw(65) << "" << endl;
	cout.fill(' ');
	cout.setf(ios::right);

	cout << setw(65) << "Balance: $ ";
	cout.width(8);
	cout << Balance << endl;
	cout.unsetf(ios::right);


	return 0;
}

