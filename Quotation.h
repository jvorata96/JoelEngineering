#pragma once


#include <string>
#include <stdint.h>
#include <vector>
#include <memory>

#include "SQL.h"
#include "Material.h"
#include "Utilities.h"


class Quotation
{
public:
	Quotation(std::string name, std::shared_ptr<SQL> sql)
		: name(name),
		  sql(sql)
	{};

	void AddMaterial();

private:
	float Total(std::shared_ptr<Material> material, float qty);


	std::string name{};
	std::shared_ptr<SQL> sql;

	std::vector<float> qty_list{};

	std::vector<std::shared_ptr<Material>> mtl_list{};
	int flag = 0;
	float overallTotal = 0;
};

