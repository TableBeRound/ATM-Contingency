// Random comment

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
	char accountNumber[15];
	char customerNumber[15];
	// I added this attribute in case the ATM expands 
	// its functionality to accomodate more than just 
	// checking accounts.
	char accountType; 
	float balance;

public:	
	Account();
	~Account();

	float GetAccountBalance();
	void WithdrawFunds(float withdrawalAmount);
	void DepositFunds(float depositAmount);
	void TransferFundsToAnotherAccount(char destinationAccountNumber, 
									   float amountToTransfer);
	void GenerateTransactionHistory();
	void CloseAccount();
};

#endif