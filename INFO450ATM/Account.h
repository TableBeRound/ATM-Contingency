

#ifndef ACCOUNT_H
#define ACCOUNT_H

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
	char _accountType; 
	double _balance;

public:	
	Account(int accountNumber, int customerNumber, char accountType, double balance);
	~Account();

	int GetAccountNumber();
	int GetCustomerNumber();
	char GetAccountType();
	double GetAccountBalance();
	void WithdrawFunds(float withdrawalAmount);
	void DepositFunds(float depositAmount);
	void TransferFundsToAnotherAccount(char destinationAccountNumber, 
									   float amountToTransfer);
	void GenerateTransactionHistory();
	void CloseAccount();
};

#endif