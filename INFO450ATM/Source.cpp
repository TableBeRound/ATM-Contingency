// Danny Glidewell, Tucker Lavell, Anthony Tran, Joshua Blanton, Ian Renninger
// TR 5:30-6:45
// Assignment: ATM Revisited

#include <iostream>
#include <cmath>
#include "Windows.h"
#include "Conio.h"
#include "UI.h"
#include "ATM.h"
#include "Database.h"
#include "Customer.h"

// 121 is the integer returned by _getch() when the "Y" key is pressed on the keyboard
#define KEY_Y 121 // This is used for determining when to close the program.

using namespace std;

int main() {
	// Boolean value for determining when to shutdown the ATM
	bool atmShutdown = false;

	ATM *atm = new ATM();

	do
	{
		if (atm->Login())
		{
			atm->MainMenu();
		
		}
		// Prompt the user whether they would like to close the program
		cout << "\n\n\nStrike the \" Y \" key to close the program. Press any other key to continue.";

		// Get the integer value corresponding to the key that they struck
		int key = _getch();

		// If the user has struck the "Y" key, they intend on closing the program.
		switch (key)
		{		
		case KEY_Y:
			atmShutdown = true;
			break;
		}			
	} while (!atmShutdown);		

	//ATM shutdown procedure should go here!!!
	delete atm;

#pragma region Load the Database
	//Database *db = new Database();

	/*Load the Customer Table*/
	//Customer *customer;
	//customer = db->createCustomer("Lavell", "Tucker", "lavelltj@vcu.edu", 2222);

	//cout << "Customer Number: " << customer->GetCustomerNumber() << "\n"
	//	<< "Customer First Name: " << customer->GetFirstName() << "\n"
	//	<< "Customer Last Name: " << customer->GetLastName() << "\n"
	//	<< "Customer Email Address: " << customer->GetEmailAddress() << "\n"
	//	<< "Customer PIN: " << customer->GetPIN() << "\n";

	//cout << "\n\n";

	///*Load the Account Table*/
	//Account *account;
	//account = db->createAccount(customer->GetCustomerNumber(), "C");	

	//cout << "Account Number: " << account->GetAccountNumber() << "\n"
	//	<< "Customer Number: " << account->GetCustomerNumber() << "\n"
	//	<< "Account Type: " << account->GetAccountType() << "\n"
	//	<< "Account Balance: " << account->GetAccountBalance() << "\n";

	//cout << "\n\n";

	//system("pause");

#pragma endregion

#pragma region ATM tests
	
	/*bool loginSuccess = atm->login();

	if (loginSuccess)
	{
		cout << "\n\nLogin Success! \n\n";
	}
	else
	{
		cout << "\n\nLogin Unsuccessfull...\n\n";
	}	

	system("pause");*/
#pragma endregion	

#pragma region Dannys Database Tests
	//Database *db = new Database();

#pragma region Database Tests Related to Customer Table
	/*
	Customer *customer; 
	customer = db->createCustomer("Glidewell", "Danny", "dglidewell@vcu.edu", 1111);

	cout << "Customer Number: " << customer->GetCustomerNumber() << "\n"
		<< "Customer First Name: " << customer->GetFirstName() << "\n"
		<< "Customer Last Name: " << customer->GetLastName() << "\n"
		<< "Customer Email Address: " << customer->GetEmailAddress() << "\n"
		<< "Customer PIN: " << customer->GetPIN() << "\n";

	cout << "\n\n";
	*/

	/*
	Customer *customer;
	customer = db->getCustomer("lavelltj@vcu.edu");
	cout << "Customer Number: " << customer->GetCustomerNumber() << "\n"
		<< "Customer First Name: " << customer->GetFirstName() << "\n"
		<< "Customer Last Name: " << customer->GetLastName() << "\n"
		<< "Customer Email Address: " << customer->GetEmailAddress() << "\n"
		<< "Customer PIN: " << customer->GetPIN() << "\n";
	cout << "\n\n";
	*/

	/*
	if (db->deleteCustomer("lavelltj@vcu.edu"))
		cout << "Record deleted. \n\n";
	else
		cout << "No record deleted. \n\n";

	customer = db->getCustomer("lavelltj@vcu.edu");
	cout << "Customer Number: " << customer->GetCustomerNumber() << "\n"
		<< "Customer First Name: " << customer->GetFirstName() << "\n"
		<< "Customer Last Name: " << customer->GetLastName() << "\n"
		<< "Customer Email Address: " << customer->GetEmailAddress() << "\n"
		<< "Customer PIN: " << customer->GetPIN() << "\n";
	cout << "\n\n";
	*/

#pragma endregion

#pragma region Database Tests Related to Account Table
	/*****************************
	* Creation & Retrieval Tests *
	******************************/
	/*
	Customer *customer = db->getCustomer("lavelltj@vcu.edu");

	Account *account;
	account = db->createAccount(customer->GetCustomerNumber(), "C");
	account = db->getAccount(customer->GetCustomerNumber());

	cout << "Account Number: " << account->GetAccountNumber() << "\n" 
		<< "Customer Number: " << account->GetCustomerNumber() << "\n" 
		<< "Account Type: " << account->GetAccountType() << "\n" 
		<< "Account Balance: " << account->GetAccountBalance() << "\n";

	cout << "\n\n";
	*/	

	/******************
	 * Deletion Tests *
	 ******************/
	/*
	Customer *customer = db->getCustomer("dglidewell@vcu.edu");
	Account *account = db->getAccount(customer->GetCustomerNumber());
	if (db->deleteAccount(account->GetAccountNumber()))
		cout << "Account #" + std::to_string(account->GetAccountNumber()) +" deleted.";
	else
		cout << "Account doesn't exist.";
	
	cout << "\n\n";
	*/

	/****************************************************************************************************
	 * Update Balance Tests  - NO LONGER WORKS BECAUSE "updateBalance()" doesn't return a boolean value *
	 ****************************************************************************************************/
	/*	
	Customer *customer = db->getCustomer("dglidewell@vcu.edu");
	Account *account = db->getAccount(customer->GetCustomerNumber());
	cout << "Account Number: " << account->GetAccountNumber() << "\n"
		<< "Customer Number: " << account->GetCustomerNumber() << "\n"
		<< "Account Type: " << account->GetAccountType() << "\n"
		<< "Account Balance: " << account->GetAccountBalance() << "\n";

	cout << "\n\n";

	double newBalance = 750;
	if (db->updateBalance(account->GetAccountNumber(), newBalance))
	{
		account = db->getAccount(customer->GetCustomerNumber());
		cout << "Account Number: " << account->GetAccountNumber() << "\n"
			<< "Customer Number: " << account->GetCustomerNumber() << "\n"
			<< "Account Type: " << account->GetAccountType() << "\n"
			<< "Account Balance: " << account->GetAccountBalance() << "\n";

		cout << "\n\n";
	}
	else
	{
		cout << "Transaction Unsuccessful\n\n";
	}*/
	
#pragma endregion

#pragma region Database Tests Related to AccountTransaction Table
	/*****************************
	* Creation & Retrieval Tests *
	******************************/
	/*
	Customer *customer = db->getCustomer("dglidewell@vcu.edu");
	Account *account = db->getAccount(customer->GetCustomerNumber());

	double transAmt = 7.11;
	string transType = "D";
	db->createTransaction(account->GetAccountNumber(), transAmt, transType);

	Transaction *transaction = db->getTransaction(10);

	cout << "Transaction Number: " << transaction->GetTransactionNumber() << "\n"
		<< "Account Number: " << transaction->GetAccountNumber() << "\n"
		<< "Transaction Amount: " << transaction->GetTransactionAmount() << "\n"
		<< "Transaction Type: " << transaction->GetTransactionType() << "\n"
		<< "Transaction Date: " << transaction->GetDate();

	cout << "\n\n";

	system("pause");
	*/	

	/******************
	* Deletion Tests *
	******************/
	/*	
	int numOfTransactionToBeDeleted = 1;
	Transaction *transaction = db->getTransaction(numOfTransactionToBeDeleted);
	cout << "Transaction Number: " << transaction->GetTransactionNumber() << "\n"
	<< "Account Number: " << transaction->GetAccountNumber() << "\n"
	<< "Transaction Amount: " << transaction->GetTransactionAmount() << "\n"
	<< "Transaction Type: " << transaction->GetTransactionType() << "\n"
	<< "Transaction Date: " << transaction->GetDate();

	cout << "\n\n";

	if (db->deleteTransaction(numOfTransactionToBeDeleted))
		cout << "Transaction #" + std::to_string(transaction->GetTransactionNumber()) +" deleted.";
	else
		cout << "Transaction doesn't exist.";

	cout << "\n\n";
	
	transaction = db->getTransaction(numOfTransactionToBeDeleted);
	cout << "Transaction Number: " << transaction->GetTransactionNumber() << "\n"
		<< "Account Number: " << transaction->GetAccountNumber() << "\n"
		<< "Transaction Amount: " << transaction->GetTransactionAmount() << "\n"
		<< "Transaction Type: " << transaction->GetTransactionType() << "\n"
		<< "Transaction Date: " << transaction->GetDate();

	cout << "\n\n";
	*/
	
#pragma endregion

#pragma region Database Tests Related to AccountTransfer Table
	/*****************************
	* Creation & Retrieval Tests *
	******************************/
	/*Customer *customer = db->getCustomer("lavelltj@vcu.edu");
	Account *account = db->getAccount(customer->GetCustomerNumber());

	int destAcct = 1;
	double transAmt = 7.11;
	db->createTransfer(account->GetAccountNumber(), destAcct, transAmt);

	Transfer *transfer = db->getTransfer(4);

	cout << "Transfer Number: " << transfer->GetTransactionNumber() << "\n"
		<< "Source Account Number: " << transfer->GetAccountNumber() << "\n"
		<< "Destination Account Number: " << transfer->GetDestinationAccountNumber() << "\n"
		<< "Transfer Amount: " << transfer->GetTransactionAmount() << "\n"
		<< "Transaction Date: " << transfer->GetDate();

	cout << "\n\n";

	system("pause");*/

	/******************
	 * Deletion Tests *
	 ******************/
	/*
	int numOfTransferToBeDeleted = 2;
	Transfer *transfer = db->getTransfer(numOfTransferToBeDeleted);
	cout << "Transfer Number: " << transfer->GetTransactionNumber() << "\n"
		<< "Source Account Number: " << transfer->GetAccountNumber() << "\n"
		<< "Destination Account Number: " << transfer->GetDestinationAccountNumber() << "\n"
		<< "Transfer Amount: " << transfer->GetTransactionAmount() << "\n"
		<< "Transaction Date: " << transfer->GetDate();

	cout << "\n\n";

	if (db->deleteTransfer(numOfTransferToBeDeleted))
		cout << "Transfer #" + std::to_string(transfer->GetTransactionNumber()) + " deleted.";
	else
		cout << "Transfer doesn't exist.";

	cout << "\n\n";
	
	transfer = db->getTransfer(numOfTransferToBeDeleted);
	cout << "Transfer Number: " << transfer->GetTransactionNumber() << "\n"
		<< "Source Account Number: " << transfer->GetAccountNumber() << "\n"
		<< "Destination Account Number: " << transfer->GetDestinationAccountNumber() << "\n"
		<< "Transfer Amount: " << transfer->GetTransactionAmount() << "\n"
		<< "Transaction Date: " << transfer->GetDate();

	cout << "\n\n";
	*/
#pragma endregion

	//system("pause");
#pragma endregion

	return 0;
}
