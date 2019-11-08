#pragma once

#include <iostream>
#include <Windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

using namespace std;

class SQL
{
public:
	SQL();
	~SQL();
	
	void Connect();
	
	void ShowData();
	void Add(std::string name, std::string price);
	

private:
	void Disconnect();
	void ShowSQLError(unsigned int handleType, const SQLHANDLE& handle);
	SQLHANDLE SQLEnvHandle = NULL;
	SQLHANDLE SQLConnHandle = NULL;
	SQLHANDLE SQLStatementHandle = NULL;
	SQLRETURN retCode = 0;
};

