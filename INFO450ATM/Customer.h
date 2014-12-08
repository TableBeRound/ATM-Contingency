#ifndef CUSTOMER_H
#define CUSTOMER_H

#pragma once
#include "Person.h"
#include <string>

using namespace std;

// Customer inherits all those basic attributes
// of the Person class plus some customer-specific
// attributes and behaviors.
class Customer :
	public Person
{
	// Despite being a number, no math is 
	// being performed on customerNumber, 
	// so I defined it and other similar
	// attributes in other classes as char 
	// arrays rather than a numeric datatype.
	int _customerNumber;
	string _emailAddress;
	string _custFirstName;
	string _custLastName;
	int _PIN;

public:	
	Customer();
	Customer(int custNum, string lastName, string firstName, string emailAddress, int pin);
	~Customer();

	//Get Functions
	int GetCustomerNumber();
	string GetEmailAddress();
	string GetFirstName();
	string GetLastName();
	int GetPIN();

	// I can't decide if some of these functions are behaviors  
	// of the Account class or the Customer class...
	void OpenNewAccount();
	void ViewListOfAccounts();
	void MakeDeposit(float depositAmount); // <---- Especially this one...
	void MakeWithdrawal(float withdrawalAmount); // <---- ...and this one
};

#endif