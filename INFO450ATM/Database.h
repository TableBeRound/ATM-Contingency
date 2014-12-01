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

#pragma region Constructor & Destructor
	// Initialize our database for usage,
	// ensuring that all tables are provisioned
	Database() 
	{
		// create and open database
		SQLiteDatabase *pDatabase = this->connect();
		// create statement instance for sql queries/statements
		SQLiteStatement *pStmt = this->createStatement(pDatabase);

		pStmt->SqlStatement("CREATE TABLE IF NOT EXISTS Customer (customerNumber INTEGER NOT NULL PRIMARY KEY, lastName VARCHAR(80), firstName VARCHAR(80), emailAddress VARCHAR(80) NOT NULL, PIN INTEGER NOT NULL)");
		pStmt->SqlStatement("CREATE TABLE IF NOT EXISTS Account (accountNumber INTEGER NOT NULL PRIMARY KEY, customerNumber INTEGER NOT NULL, accountType CHAR NOT NULL, balance FLOAT NOT NULL)");
		//pStmt->SqlStatement("CREATE TABLE IF NOT EXISTS Transaction (customerNumber INTEGER NOT NULL PRIMARY KEY, lastName VARCHAR(80), firstName VARCHAR(80), emailAddress VARCHAR(80) NOT NULL, PIN INTEGER NOT NULL)");
		//pStmt->SqlStatement("CREATE TABLE IF NOT EXISTS Transfer (customerNumber INTEGER NOT NULL PRIMARY KEY, lastName VARCHAR(80), firstName VARCHAR(80), emailAddress VARCHAR(80) NOT NULL, PIN INTEGER NOT NULL)");
	}

	// Destructor
	~Database()
	{
	}
#pragma endregion

#pragma region Functions related to Customer objects
	// Create Customer Function: 
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
		int customerNumber = pStmt->GetColumnInt(0); // get the int value at the zeroth column 

		/*************************************************************************************** 
		 * Notice how each pStmt is first "loaded" with an SQL statement via the Sql() function
		 * then executed with either the Execute() or ExecuteAndFree() functions.
		 ***************************************************************************************/

		// return the customer to the calling function
		return new Customer(customerNumber, firstName, lastName, pin, emailAddress);
	}	

	// Retrieve Customer Function:
	// Function which searches the Customer table and returns a customer object based on the 
	// emailAddress which is passed to it.   NEEDS INPUT VALIDATION FOR "email" !!!
	Customer *getCustomer(string email) 
	{
		// Here are our variables which store the values which will be returned by 
		// the database search (assuming the search was successful)
		int retrievedCustomerID = 0;
		string retrievedFirstName = "";
		string retrievedLastName = "";
		int retrievedPIN = 0;
		string retrievedEmailAddress = "";

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
			retrievedCustomerID = pStmt->GetColumnInt("customerNumber");
			retrievedFirstName = pStmt->GetColumnString("firstName");
			retrievedLastName = pStmt->GetColumnString("lastName");
			retrievedPIN = pStmt->GetColumnInt("PIN");
			retrievedEmailAddress = pStmt->GetColumnString("emailAddress");
		}

		// "Clean up"
		pStmt->FreeQuery();

		// Use the variables, which have been assigned values via the query above, 
		// to create a Customer object to return.
		return new Customer(retrievedCustomerID, retrievedFirstName, retrievedLastName, retrievedPIN, retrievedEmailAddress);
	}

	// Delete Customer Function:
	// Searches the Customer table and deletes the row(s) corresponding to the 
	// email address which is passed to it.  Returns false if no changes were
	// made and true if at least one was made.
	bool deleteCustomer(string email)
	{
		// First create a pointer to a SQLiteDatabase using 
		// the connect() function defined above and then
		// create a pointer to an SQLiteStatement object.		
		SQLiteDatabase *pDatabase = this->connect();
		SQLiteStatement *pStmt = this->createStatement(pDatabase);

		pStmt->SqlStatement("DELETE FROM Customer WHERE emailAddress = '" + email + "';");

		int recordsDeleted = 0;

		recordsDeleted = pDatabase->GetTotalDatabaseChanges();

		if (recordsDeleted)
			return true;
		else
			return false;
	}
#pragma endregion 

#pragma region Functions related to Account objects
	// Create Account Function
	Account *createAccount(int customerNumber, string accountType)
	{
		double initialBalance = 0.0;
		
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
		pStmt->Sql("INSERT INTO Account (customerNumber, accountType, balance) VALUES(?, ?, ?);");
		pStmt->BindInt(1, customerNumber);      // First question mark in the VALUES() clause above
		pStmt->BindString(2, accountType);         // Second question mark in the VALUES() clause above
		pStmt->BindDouble(3, initialBalance);   // Third question mark in the VALUES() clause above

		// executes the INSERT statement and cleans-up automatically
		pStmt->ExecuteAndFree();

		// get the customer ID for the customer entry which was just made (the last row id).
		pStmt->Sql("SELECT last_insert_rowid();");
		pStmt->Execute();
		int accountNumber = pStmt->GetColumnInt(0); // get the int value at the zeroth column 

		/***************************************************************************************
		* Notice how each pStmt is first "loaded" with an SQL statement via the Sql() function
		* then executed with either the Execute() or ExecuteAndFree() functions.
		***************************************************************************************/

		char accType = accountType[0];
		// return the account to the calling function
		return new Account(accountNumber, customerNumber, accType, initialBalance);
	}
	
	// Retrieve Account Function:
	// I would like to make it so that a future version of this function accepts
	// an integer value for customerNumber rather than a string.  I believe that
	// this would make things more consistent with the other database functions
	// related to Account objects.
	Account *getAccount(string customerNumber, string accountType)
	{
		// Here are our variables which store the values which will be returned by 
		// the database search (assuming the search was successful)
		int retrievedAccountNumber = 0;
		int retrievedCustomerNumber = 0;
		string retrievedAccountType = "";
		double retrievedBalance = 0.0;

		// First create a pointer to a SQLiteDatabase using 
		// the connect() function defined above and then
		// create a pointer to an SQLiteStatement object.		
		SQLiteDatabase *pDatabase = this->connect();
		SQLiteStatement *pStmt = this->createStatement(pDatabase);
		
		// Use the customerNumber and accountType passed to this method to query the database.
		pStmt->Sql("SELECT * FROM Account WHERE customerNumber = '"+customerNumber+"' " +
			       "AND accountType = '"+accountType+"';");

		// Process the results of the query above - assigning the values of each
		// column to the variables declared above.
		while (pStmt->FetchRow())
		{
			retrievedAccountNumber = pStmt->GetColumnInt("accountNumber");
			retrievedCustomerNumber = pStmt->GetColumnInt("customerNumber");
			retrievedAccountType = pStmt->GetColumnString("accountType");
			retrievedBalance = pStmt->GetColumnDouble("balance");			
		}

		// This is a little work-around to make the Account constructor and the result from the 
		// "GetColumnString" function from Kompex's SQLiteStatement "play nice".  GetColumnString
		// returns a string, but the Account object's constructor needs a character for accountType.
		char retAccType = retrievedAccountType[0];

		// "Clean up"
		pStmt->FreeQuery();

		// Use the variables, which have been assigned values via the query above, 
		// to create a Customer object to return.
		return new Account(retrievedAccountNumber, retrievedCustomerNumber, retAccType, retrievedBalance);
	}

	// This function will encapsulate the logic to perform the various types
	// of transactions on accounts.  This includes withdrawals, deposits, 
	// and transfers.
	bool accountTransaction(double amount, char transactionType)
	{
		return false;
	}

	// Delete Account Function:
	// I should consider making a more abstract method called 
	// "deleteRow" whereby one can specify the table name and
	// the primary key of the row to be deleted.
	bool deleteAccount(string accountNumber)
	{
		// First create a pointer to a SQLiteDatabase using 
		// the connect() function defined above and then
		// create a pointer to an SQLiteStatement object.		
		SQLiteDatabase *pDatabase = this->connect();
		SQLiteStatement *pStmt = this->createStatement(pDatabase);

		pStmt->SqlStatement("DELETE FROM Account WHERE accountNumber = '" + accountNumber + "';");

		int recordsDeleted = 0;

		recordsDeleted = pDatabase->GetTotalDatabaseChanges();

		if (recordsDeleted)
			return true;
		else
			return false;
	}
#pragma endregion

#pragma region Functions related to Transaciton objects

	// Transaction: Create, Delete, Retrieve

#pragma endregion
};

