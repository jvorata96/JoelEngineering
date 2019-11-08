#include "SQL.h"

using namespace std;

SQL::SQL()
{   
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
		Disconnect();
	if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		Disconnect();
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnHandle))
		Disconnect();
	if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
		Disconnect();
};

SQL::~SQL()
{
	cout << "destructor" << endl;
	Disconnect();
};

void SQL::Connect()
{
	switch (SQLDriverConnect(SQLConnHandle, NULL, (SQLCHAR*)"DSN=JoelDB;UID=myID2;PWD=myPW2;WSID=JE-ACCOUNTS;DATABASE=myDB;", SQL_NTS, NULL, 1024, NULL, SQL_DRIVER_NOPROMPT))
	{
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:
		cout << "Database accessed successfully!" << endl;
		break;
	case SQL_NO_DATA_FOUND:
	case SQL_ERROR:
		ShowSQLError(SQL_HANDLE_DBC, SQLConnHandle);
		retCode = -1;
		break;
	default:
		break;
	}

	if (retCode == -1)
		Disconnect();
}

void SQL::Disconnect()
{
	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	cout << "disconnected" << endl;
};

void SQL::ShowData()
{
	//char SQLQuery[] = "SELECT * FROM Product";
	std::string SQLQuery = "SELECT * FROM Product";

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnHandle, &SQLStatementHandle))
		Disconnect();

	if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
	{
		ShowSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
		Disconnect();
	}
	else
	{
		char name[256];
		int cost;
		while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
		{
			SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &name, size(name), NULL);
			SQLGetData(SQLStatementHandle, 2, SQL_C_ULONG, &cost, sizeof(cost), NULL);
			cout << name << " " << cost << endl;
		}
	}
}

void SQL::Add(std::string name, std::string price)
{
	std::string SQLQuery = "INSERT INTO Product VALUES ('" + name + "', " + price + ");";

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnHandle, &SQLStatementHandle))
		Disconnect();

	if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
	{
		cout << "cant\n";
		ShowSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
		Disconnect();
	}
	else
	{
		cout << "can\n";
	}
}


void SQL::ShowSQLError(unsigned int handleType, const SQLHANDLE& handle)
{
	SQLCHAR SQLState[1024];
	SQLCHAR message[1024];
	cout << "hey4";
	if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
	{
		cout << "SQL driver message: " << message << "\nSQL State: " << SQLState << endl;
	}
};