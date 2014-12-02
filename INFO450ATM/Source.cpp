// Danny Glidewell, Tucker Lavell, Anthony Tran
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

// Class prototypes
//UI *ui = new UI();
//ATM *atm = new ATM();


int main() {
	//atm->login();

	Database *db = new Database();

#pragma region Database Tests Related to Customer Table
	//Customer *customer;
	/*customer = db->createCustomer("Danny", "Glidewell", 1111, "dglidewell@vcu.edu");

	cout << "Customer Number: " << customer->GetCustomerNumber() << "\n"
		<< "Customer First Name: " << customer->GetFirstName() << "\n"
		<< "Customer Last Name: " << customer->GetLastName() << "\n"
		<< "Customer Email Address: " << customer->GetEmailAddress() << "\n"
		<< "Customer PIN: " << customer->GetPIN() << "\n";

	cout << "\n\n";*/

	//customer = db->createCustomer("Tucker", "Lavell", 2222, "lavelltj@vcu.edu");

	/*cout << "Customer Number: " << customer->GetCustomerNumber() << "\n"
		<< "Customer First Name: " << customer->GetFirstName() << "\n"
		<< "Customer Last Name: " << customer->GetLastName() << "\n"
		<< "Customer Email Address: " << customer->GetEmailAddress() << "\n"
		<< "Customer PIN: " << customer->GetPIN() << "\n";

	cout << "\n\n";*/
	
	/*customer = db->getCustomer("dglidewell@vcu.edu");
	cout << "Customer Number: " << customer->GetCustomerNumber() << "\n"
		<< "Customer First Name: " << customer->GetFirstName() << "\n"
		<< "Customer Last Name: " << customer->GetLastName() << "\n"
		<< "Customer Email Address: " << customer->GetEmailAddress() << "\n"
		<< "Customer PIN: " << customer->GetPIN() << "\n";
	cout << "\n\n";*/
		
	/*if (db->deleteCustomer("lavelltj@vcu.edu"))
		cout << "Record deleted. \n\n";
	else
		cout << "No record deleted. \n\n";*/

	/*customer = db->getCustomer("lavelltj@vcu.edu");
	cout << "Customer Number: " << customer->GetCustomerNumber() << "\n"
		<< "Customer First Name: " << customer->GetFirstName() << "\n"
		<< "Customer Last Name: " << customer->GetLastName() << "\n"
		<< "Customer Email Address: " << customer->GetEmailAddress() << "\n"
		<< "Customer PIN: " << customer->GetPIN() << "\n";	
	cout << "\n\n";

	system("pause");*/

#pragma endregion

#pragma region Database Tests Related to Account Table
	//Account *account;
	//account = db->createAccount(5, "C");
	//account = db->getAccount("1", "S");

	//cout << "Account Number: " << account->GetAccountNumber() << "\n" //7
	//	<< "Customer Number: " << account->GetCustomerNumber() << "\n" //5
	//	<< "Account Type: " << account->GetAccountType() << "\n" //C
	//	<< "Account Balance: " << account->GetAccountBalance() << "\n"; //0

	//cout << "\n\n";

	/******************
	 * Deletion Tests *
	 ******************/
	/*string accNum = "3";

	if (db->deleteAccount(accNum))
		cout << "Account #" + accNum +" deleted.";
	else
		cout << "Account doesn't exist.";
	
	cout << "\n\n";*/
	
#pragma endregion

	double x = 100;
	double y = -50.5;
	double z = x + y;

	cout << z << "\n\n";

	system("Pause");

	return 0;
}
