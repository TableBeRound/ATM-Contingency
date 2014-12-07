#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

using namespace std;

#pragma once
class Transaction
{
protected:
	int _transactionNumber;
	int _accountNumber;	
	string _date;
	double _transactionAmount;
	// I thought about having two separate classes, one for 
	// withdrawals and one for deposits, but I determined 
	// that I was mis-identifying the transactionType attribute
	// for a class.
	char _transactionType; 

public:
	Transaction();
	Transaction(int transactionNum, int acctNum, double transactionAmt, string date, char transactionType);
	~Transaction();

	// Get & Set Funcitons
	int GetTransactionNumber();
	int GetAccountNumber();
	double GetTransactionAmount();
	string GetDate();
	char GetTransactionType();

	// Post transaction to the database and 
	// update the balance for the account stored
	// in the sourceAccountNumber variable.
	void PostTransaction();
};

#endif
