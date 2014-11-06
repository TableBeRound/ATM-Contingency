#pragma once
#include "Transaction.h"

// I opted to create a Transfer class which inherits from 
// Transaction because it needs a little bit more info than
// your typical transaction.
class Transfer :
	public Transaction
{	
	// One particular thing that it needs which transaction
	// doesn't offer is the destination account.
	char destinationAccountNumber[15];

public:
	Transfer();
	~Transfer();

	void TransferFunds(char *source, 
					   char *destination);
};

