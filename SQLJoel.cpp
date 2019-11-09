// SQLJoel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SQL.h"
#include "Quotation.h"

#include <sstream>
#include <iomanip>

#include <cstdlib>

using namespace std;

int main()
{
	std::shared_ptr<SQL> sql = std::make_shared<SQL>();
	std::string x = "junred";
	Quotation quotation(x, sql);
	sql->Connect();

	int choice = 1;
	std::string name{}, price{}, product_name{};
	
	system("mode 650");

	while (choice)
	{
		system("CLS");
		cout << "0: Quit; 1:ShowAll, 2:Add, 3:Modify, 4:Create Quotation" << endl;
		cin >> choice;
		cin.ignore(256, '\n');

		switch (choice)
		{
		case 0:
			break;
		case 1:
			sql->ShowData();
			system("PAUSE");
			break;
		case 2:
			sql->Add();
			system("PAUSE");
			break;
		case 3:
			cout << "Enter name: ";
			getline(cin, name);
			cout << "Enter price: ";
			cin >> price;
			sql->Modify(name, price);
			system("PAUSE");
			break;

		case 4:
			quotation.AddMaterial();
			system("PAUSE");
			break;

		default:
			break;
		
		}
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
