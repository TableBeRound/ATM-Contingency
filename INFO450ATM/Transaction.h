#ifndef TRANSACTION_H
#define TRANSACTION_H

#pragma once
class Transaction
{
	char sourceAccountNumber[15];
	char transactionNumber[20];
	char date[10];
	float transactionAmount;
	// I thought about having two separate classes, one for 
	// withdrawals and one for deposits, but I determined 
	// that I was mis-identifying the transactionType attribute
	// for a class.
	char transactionType; 
	
public:
	Transaction();
	~Transaction();

	
	// Post transaction to the database and 
	// update the balance for the account stored
	// in the sourceAccountNumber variable.
	void PostTransaction();
};

#endif
