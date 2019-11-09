#include "Quotation.h"

using namespace std;

void Quotation::AddMaterial()
{ 
	if (flag)
	{
		system("CLS");
		Printer_Design_Top();

		for (int i = 0; i < mtl_list.size(); i++)
		{
			Printer(mtl_list[i], Total(mtl_list[i], qty_list[i]), qty_list[i]);
		}

		Printer_Design_Bottom();
		Printer_Total(overallTotal);
	}


	string material_name{};
	cout << "Enter name: ";
	getline(cin, material_name);

	std::shared_ptr<Material> material = std::make_shared<Material>(material_name);

	sql->GetData(material);
	
	
	float qty = 1;
	cout << "Quantity of " << material->name << ": ";
	cin >> qty;
	cin.ignore(256, '\n');

	qty_list.push_back(qty);

	mtl_list.push_back(material);

	Printer_Design_Top();

	for (int i = 0; i < mtl_list.size(); i++)
	{
		Printer(mtl_list[i], Total(mtl_list[i], qty_list[i]), qty_list[i]);
	}

	Printer_Design_Bottom();
	overallTotal += Total(material, qty);
	Printer_Total(overallTotal);

	cout << "0: Back to Main Menu; 1: Add more Materials" << endl;

	int choice;
	cin >> choice;
	cin.ignore(256, '\n');

	if (choice == 1)
	{
		flag = 1;
		AddMaterial();
	}
	else if (choice == 0)
		return;


	return;
}

float Quotation::Total(std::shared_ptr<Material> material, float qty)
{
	
	float total = qty * ((1 + material->markup) * (material->mat_cost + (material->set_hr * material->set_hr_$ / qty) + (material->opt_hr * material->opt_hr_$)));
	return total;
}
