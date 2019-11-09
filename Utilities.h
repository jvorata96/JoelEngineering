#pragma once

#include <iostream>
#include "Material.h"

using namespace std;

static void Printer_Design_Top()
{
	cout << left << setw(7) << setfill('-') << left << '+'
		<< setw(41) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << '+' << '+' << endl;

	cout << setfill(' ') << '|' << left << setw(6)
		<< "Qty"
		<< setfill(' ') << '|' << setw(40) << "Material Name"
		<< setfill(' ') << '|' << setw(20) << "Material Price"
		<< setfill(' ') << '|' << setw(20) << "Setup Hr"
		<< setfill(' ') << '|' << setw(20) << "Setup $/Hr"
		<< setfill(' ') << '|' << setw(20) << "Operation Hr"
		<< setfill(' ') << '|' << setw(20) << "Operation $/Hr"
		<< setfill(' ') << '|' << setw(20) << "Markup"
		<< setfill(' ') << '|' << right << setw(20)
		<< "Total" << '|' << endl;

	cout << left << setw(7) << setfill('-') << left << '+'
		<< setw(41) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << '+' << '+' << endl;
}

static void Printer(std::shared_ptr<Material> material, float total, float qty)
{
	cout << setfill(' ') << '|' << left << setw(6) << qty
		<< setfill(' ') << '|' << setw(40) << material->name
		<< setfill(' ') << '|' << setw(20) << material->mat_cost
		<< setfill(' ') << '|' << setw(20) << material->set_hr
		<< setfill(' ') << '|' << setw(20) << material->set_hr_$
		<< setfill(' ') << '|' << setw(20) << material->opt_hr
		<< setfill(' ') << '|' << setw(20) << material->opt_hr_$
		<< setfill(' ') << '|' << setw(20) << material->markup
		<< setfill(' ') << '|' << right << setw(20)
		<< total << '|' << endl;
}

static void Printer_Design_Bottom()
{
	cout << left << setw(7) << setfill('-') << left << '+'
		<< setw(41) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << left << '+'
		<< setw(21) << setfill('-') << '+' << '+' << endl;
}

static void Printer_Total(float overallTotal)
{
	cout << right << setw(175) << setfill(' ') << '|' << right << setw(20) << overallTotal << '|' << endl;
	cout << right << setw(175) << setfill(' ') << '+' << right << setw(21) << setfill('-') << '+' << endl;

}