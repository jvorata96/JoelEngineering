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

void SQL::GetData(std::shared_ptr<Material> material)
{
	std::string SQLQuery = "SELECT * FROM dbo.JoelProducts WHERE Name = '" + material->name + "'";
	//cout << SQLQuery << endl;

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnHandle, &SQLStatementHandle))
		Disconnect();

	if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
	{
		ShowSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
		Disconnect();
	}
	else
	{
		int setup_hr;
		float cost, set_hr, set_$, opt_hr, opt_$, markup;
		while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
		{
			SQLGetData(SQLStatementHandle, 2, SQL_C_FLOAT, &cost, sizeof(cost), NULL);
			SQLGetData(SQLStatementHandle, 3, SQL_C_FLOAT, &set_hr, sizeof(set_hr), NULL);
			SQLGetData(SQLStatementHandle, 4, SQL_C_FLOAT, &set_$, sizeof(set_$), NULL);
			SQLGetData(SQLStatementHandle, 5, SQL_C_FLOAT, &opt_hr, sizeof(opt_hr), NULL);
			SQLGetData(SQLStatementHandle, 6, SQL_C_FLOAT, &opt_$, sizeof(opt_$), NULL);
			SQLGetData(SQLStatementHandle, 7, SQL_C_FLOAT, &markup, sizeof(markup), NULL);
			//cout << cost << "this the cost" << endl; // remove duplicates!!!!!
			material->mat_cost = cost;
			material->set_hr = set_hr;
			material->set_hr_$ = set_$;
			material->opt_hr = opt_hr;
			material->opt_hr_$ = opt_$;
			material->markup = markup;
		}
	}

};

void SQL::ShowData()
{
	std::string SQLQuery = "SELECT * FROM JoelProducts";

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
		float cost, set_hr, set_$, opt_hr, opt_$, markup;

		Printer_Design_Top();

		while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
		{
			SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &name, size(name), NULL);
			SQLGetData(SQLStatementHandle, 2, SQL_C_FLOAT, &cost, sizeof(cost), NULL);
			SQLGetData(SQLStatementHandle, 3, SQL_C_FLOAT, &set_hr, sizeof(set_hr), NULL);
			SQLGetData(SQLStatementHandle, 4, SQL_C_FLOAT, &set_$, sizeof(set_$), NULL);
			SQLGetData(SQLStatementHandle, 5, SQL_C_FLOAT, &opt_hr, sizeof(opt_hr), NULL);
			SQLGetData(SQLStatementHandle, 6, SQL_C_FLOAT, &opt_$, sizeof(opt_$), NULL);
			SQLGetData(SQLStatementHandle, 7, SQL_C_FLOAT, &markup, sizeof(markup), NULL);

			cout << setfill(' ') << '|' << left << setw(6) << "1"
				<< setfill(' ') << '|' << setw(40) << name
				<< setfill(' ') << '|' << setw(20) << cost
				<< setfill(' ') << '|' << setw(20) << set_hr
				<< setfill(' ') << '|' << setw(20) << set_$
				<< setfill(' ') << '|' << setw(20) << opt_hr
				<< setfill(' ') << '|' << setw(20) << opt_$
				<< setfill(' ') << '|' << setw(20) << markup
				<< setfill(' ') << '|' << right << setw(20)
				<< "Total" << '|' << endl;

		}
		
		Printer_Design_Bottom();
	}
};

void SQL::Add()
{

	std::string name{}, price, set_hr, set_$, opt_hr, opt_$, markup;

	cout << "Enter name: ";
	getline(cin, name);

	cout << "Material Cost: ";
	getline(cin, price);

	cout << "Setup Hr: ";
	getline(cin, set_hr);

	cout << "Setup $/Hr: ";
	getline(cin, set_$);

	cout << "Operation Hr: ";
	getline(cin, opt_hr);

	cout << "Operation $/Hr: ";
	getline(cin, opt_$);
	
	cout << "Markup: ";
	getline(cin, markup);

	std::string SQLQuery = "INSERT INTO JoelProducts VALUES ('" + name + "', " + price +  ", " + set_hr + ", " + set_$ + ", " + opt_hr + ", " + opt_$ + ", " + markup + ");";

	cout << SQLQuery << endl;

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
};

void SQL::Modify(std::string name, std::string price)
{
	std::string SQLQuery = "UPDATE Product SET [Material Cost] = " + price + " WHERE Name = '" + name + "';";
	cout << SQLQuery << endl;

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
};


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