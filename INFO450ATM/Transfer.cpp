#include "Transfer.h"

// Typical constructor for Transfer object
Transfer::Transfer(int transactionNum, int sourceAcctNum, int destinationAcctNum, double transactionAmt, string date, string transactionType)
{
	this->_transactionNumber = transactionNum;
	this->_accountNumber = sourceAcctNum;
	this->_destinationAccountNumber = destinationAcctNum;
	this->_transactionAmount = transactionAmt;
	this->_date = date;
	this->_transactionType = transactionType;
}


Transfer::~Transfer()
{
}

// Get Function
int Transfer::GetDestinationAccountNumber()
{
	return this->_destinationAccountNumber;
}

void Transfer::TransferFunds(char *source, char *destination)
{

}