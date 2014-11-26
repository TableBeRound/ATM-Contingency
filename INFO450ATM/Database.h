// This class was based on the "DataContext" class given by the professor

#pragma once
#include "KompexSQLitePrerequisites.h"
#include "KompexSQLiteDatabase.h"
#include "KompexSQLiteStatement.h"
#include "KompexSQLiteException.h"
#include "KompexSQLiteStreamRedirection.h"
#include "KompexSQLiteBlob.h"
#include "sqlite3.h"
#include "sqlite3ext.h"

#include <iostream>
#include <exception>
#include "Account.h"
#include "Customer.h"
#include "Transaction.h"
#include "Transfer.h"

using namespace Kompex;
using namespace std;

class Database
{
	SQLiteDatabase *connect() {
		return new SQLiteDatabase("test.db", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0);
	}

	SQLiteStatement *createStatement(SQLiteDatabase *pDatabase) {
		return new SQLiteStatement(pDatabase);
	}

public:
	// Constructor 
	// Initialize our database for usage,
	// ensuring that all tables are provisioned
	Database() 
	{
		// create and open database
		SQLiteDatabase *pDatabase = this->connect();
		// create statement instance for sql queries/statements
		SQLiteStatement *pStmt = this->createStatement(pDatabase);

		pStmt->SqlStatement("CREATE TABLE IF NOT EXISTS Customer (customerId INTEGER NOT NULL PRIMARY KEY, lastName VARCHAR(80), firstName VARCHAR(80), emailAddress VARCHAR(80) NOT NULL, PIN INTEGER NOT NULL)");
	}

	// Destructor
	~Database()
	{
	}

	// This is the function used to create a customer entry in the database.
	Customer *createCustomer(string firstName, string lastName, int pin, string emailAddress) 
	{
		// First create a pointer to a SQLiteDatabase using 
		// the connect() function defined above and then
		// create a pointer to an SQLiteStatement object.		
		SQLiteDatabase *pDatabase = this->connect();
		SQLiteStatement *pStmt = this->createStatement(pDatabase);  // Notice how the SQLiteStatement 
																	// pointer (pStmt) is "tied" to the 
		                                                            // SQLiteDatabase object that pDatabase 
																	// points to.

		// Use the SQLiteStatement pointer (pStmt) created 
		// above to send a SQL statement to the database.
		pStmt->Sql("INSERT INTO Customer (lastName, firstName, PIN, emailAddress) VALUES(?, ?, ?, ?);");
		pStmt->BindString(1, lastName);      // First question mark in the VALUES() clause above
		pStmt->BindString(2, firstName);     // Second question mark in the VALUES() clause above
		pStmt->BindInt(3, pin);              // Third question mark in the VALUES() clause above
		pStmt->BindString(4, emailAddress);  // Fourth question mark in the VALUES() clause above

		// executes the INSERT statement and cleans-up automatically
		pStmt->ExecuteAndFree();

		// get the customer ID for the customer entry which was just made (the last row id).
		pStmt->Sql("SELECT last_insert_rowid();");
		pStmt->Execute();
		int customerId = pStmt->GetColumnInt(0); // get the int value at the zeroth column 

		/*************************************************************************************** 
		 * Notice how each pStmt is first "loaded" with an SQL statement via the Sql() function
		 * then executed with either the Execute() or ExecuteAndFree() functions.
		 ***************************************************************************************/

		// return the customer to the calling function
		return new Customer(customerId, firstName, lastName, pin, emailAddress);
	}	

	// Function which searches the database and returns a customer object based on the 
	// emailAddress which is passed to it.
	Customer *getCustomer(string email) 
	{
		// Here are our variables which store the values which will be returned by 
		// the database search (assuming the search was successful)
		int customerID;
		string firstName;
		string lastName;
		int pin;
		string emailAddress;

		// First create a pointer to a SQLiteDatabase using 
		// the connect() function defined above and then
		// create a pointer to an SQLiteStatement object.		
		SQLiteDatabase *pDatabase = this->connect();
		SQLiteStatement *pStmt = this->createStatement(pDatabase);

		// Use the email address passed to this method to query the database.
		pStmt->Sql("SELECT * FROM Customer WHERE emailAddress = '" + email + "';");

		// Process the results of the query above - assigning the values of each
		// column to the variables declared above.
		while (pStmt->FetchRow())
		{
			customerID = pStmt->GetColumnInt("customerId");
			firstName = pStmt->GetColumnString("firstName");
			lastName = pStmt->GetColumnString("lastName");
			pin = pStmt->GetColumnInt("PIN");
			emailAddress = pStmt->GetColumnString("emailAddress");
		}

		// "Clean up"
		pStmt->FreeQuery();

		// Use the variables, which have been assigned values via the query above, 
		// to create a Customer object to return.
		return new Customer(customerID, firstName, lastName, pin, emailAddress);
	}

	bool deleteCustomer()
	{
		return false;
	}

	// Account: Create, Delete, Update, Retrieve

	// Transaction: Create, Delete, Retrieve
};

