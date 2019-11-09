#pragma once

#include <iostream>
#include <Windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

#include <sstream>
#include <iomanip>

#include <cstdlib>

#include "Material.h"
#include "Utilities.h"

using namespace std;

class SQL
{
public:
	SQL();
	~SQL();
	
	void Connect();
	
	void ShowData();
	void GetData(std::shared_ptr<Material> material);
	void Add();
	void Modify(std::string name, std::string price);

private:
	void Disconnect();
	void ShowSQLError(unsigned int handleType, const SQLHANDLE& handle);
	SQLHANDLE SQLEnvHandle = NULL;
	SQLHANDLE SQLConnHandle = NULL;
	SQLHANDLE SQLStatementHandle = NULL;
	SQLRETURN retCode = 0;
};

