// Danny Glidewell, Tucker Lavell, Anthony Tran, Joshua Blanton, Ian Renninger
// TR 5:30-6:45
// Assignment: ATM Redo
// This program will simulate a text based version of an ATM interface and interaction
// for the Shallow prototype of the ATM, there are only successful interactions with this ATM

#include <iostream>
#include <cmath>
#include "Windows.h"
#include "Conio.h"
#include "UI.h"
#include "ATM.h"
#include "Database.h"
#include "Customer.h"

using namespace std;

int main() {

	// Boolean value for determining when to shutdown the ATM
	bool atmShutdown = false;
	ATM *atm = new ATM();

	do
	{
		if (atm->Login())
			atm->MainMenu();

		cout << "\n\nStrike the \" Y \" key to close the program. Press any other key to continue.";
		int c = _getch();
		switch (c)
		{
		case 121:
			atmShutdown = true;
			break;
		}			

	} while (!atmShutdown);		

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

	/************************
	 * Update Balance Tests *
	 ************************/
	/*	
	Customer *customer = db->getCustomer("dglidewell@vcu.edu");
	Account *account = db->getAccount(customer->GetCustomerNumber());
	cout << "Account Number: " << account->GetAccountNumber() << "\n"
		<< "Customer Number: " << account->GetCustomerNumber() << "\n"
		<< "Account Type: " << account->GetAccountType() << "\n"
		<< "Account Balance: " << account->GetAccountBalance() << "\n";

	cout << "\n\n";

	double depositAmount = 750;
	if (db->updateBalance(account->GetAccountNumber(), depositAmount))
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
	}
	*/
#pragma endregion

#pragma region Database Tests Related to Transaction Table
	/*****************************
	* Creation & Retrieval Tests *
	******************************/
	/*
	Customer *customer = db->getCustomer("dglidewell@vcu.edu");
	Account *account = db->getAccount(customer->GetCustomerNumber());

	double transAmt = 13.13;
	string transType = "D";
	string transDate = "12/08/2014";
	Transaction *transaction = db->createTransaction(account->GetAccountNumber(), transAmt, transType, transDate);
	cout << "Transaction Number: " << transaction->GetTransactionNumber() << "\n"
		<< "Account Number: " << transaction->GetAccountNumber() << "\n"
		<< "Transaction Amount: " << transaction->GetTransactionAmount() << "\n"
		<< "Transaction Type: " << transaction->GetTransactionType() << "\n"
		<< "Transaction Date: " << transaction->GetDate();

	cout << "\n\n";
	*/

	/*
	Transaction *transaction = db->getTransaction(7);
	cout << "Transaction Number: " << transaction->GetTransactionNumber() << "\n"
		<< "Account Number: " << transaction->GetAccountNumber() << "\n"
		<< "Transaction Amount: " << transaction->GetTransactionAmount() << "\n"
		<< "Transaction Type: " << transaction->GetTransactionType() << "\n"
		<< "Transaction Date: " << transaction->GetDate();

	cout << "\n\n";
	*/	

	/******************
	* Deletion Tests *
	******************/
	/*	
	int numOfTransactionToBeDeleted = 2;
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

	//system("pause");
#pragma endregion

	

	return 0;
}
