#ifndef TRANSFER_H
#define TRANSFER_H

#pragma once
#include "Transaction.h"
#include <string>

using namespace std;

// I opted to create a Transfer class which inherits from 
// Transaction because it needs a little bit more info than
// your typical transaction.
class Transfer :
	public Transaction
{	
	// The destination account number is one particular thing 
	// a transfer object needs that a transaction doesn't have.
	int _destinationAccountNumber;

public:
	Transfer(int transactionNum, int sourceAcctNum, int destinationAcctNum, double transactionAmt, string date);
	Transfer(int sourceAcctNum, int destinationAcctNum, double transactionAmt);
	~Transfer();

	int GetDestinationAccountNumber();
};

#endif // !TRANSFER_H