#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

using namespace std;

#pragma once

class Account
{
	// Despite being a number, no math is 
	// being performed on accountNumber, 
	// so I defined it and other similar
	// attributes in other classes as char 
	// arrays rather than a numeric datatype.
	int _accountNumber;
	int _customerNumber;
	// I added this attribute in case the ATM expands 
	// its functionality to accomodate more than just 
	// checking accounts.
	string _accountType; 
	double _balance;
	string _accountStatus;

public:	
	Account(int accountNumber, int customerNumber, string accountType, double balance, string accountStatus);
	~Account();

	int GetAccountNumber();
	int GetCustomerNumber();
	string GetAccountType();
	double GetAccountBalance();
	string GetAccountStatus();
	void SetAccountStatus(string status);
	void SetAccountBalance(double newAccountBalance);
	void CloseAccount();
};

#endif