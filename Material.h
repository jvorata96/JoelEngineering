#pragma once

#include <stdint.h>
#include <string>


class Material
{
public:
	Material(std::string name)
		: name(name) {};

	float mat_cost{};
	float set_hr{};
	float set_hr_${};
	float opt_hr{};
	float opt_hr_${};
	float markup{};
	std::string name{};
};

