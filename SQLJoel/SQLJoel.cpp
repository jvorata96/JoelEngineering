// SQLJoel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SQL.h"

using namespace std;

int main()
{
	SQL sql;
	sql.Connect();

	int choice = 0;
	std::string name{}, price{};
	cout << "0: Quit; 1:ShowAll, 2:Add" << endl;
	cin >> choice;
	while (choice)
	{
		switch (choice)
		{
		case 0:
			break;
		case 1:
			sql.ShowData();
			break;
		case 2:
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter price: ";
			cin >> price;
			sql.Add(name, price);
			break;
		default:
			break;
		}
		cout << "0: Quit; 1:ShowAll, 2:Add" << endl;
		cin >> choice;
	}


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
