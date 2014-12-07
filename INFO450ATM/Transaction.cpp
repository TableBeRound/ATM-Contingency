#include "Transaction.h"

// Default Constructor for Transaction objects
Transaction::Transaction()
{
	this->_transactionNumber = 0;
	this->_accountNumber = 0;
	this->_transactionAmount = 0.0;
	this->_date = "------";
	this->_transactionType = "NULL";
}

// Typical Constructor for Transaction objects
Transaction::Transaction(int transactionNum, int acctNum, double transactionAmt, string date, string transactionType)
{
	this->_transactionNumber = transactionNum;
	this->_accountNumber = acctNum;
	this->_transactionAmount = transactionAmt;
	this->_date = date;
	this->_transactionType = transactionType;
}

Transaction::~Transaction()
{
}

// Get and Set Functions
int Transaction::GetTransactionNumber()
{
	return this->_transactionNumber;
}

int Transaction::GetAccountNumber()
{
	return this->_accountNumber;
}

double Transaction::GetTransactionAmount()
{
	return this->_transactionAmount;
}

string Transaction::GetDate()
{
	return this->_date;
}

string Transaction::GetTransactionType()
{
	return this->_transactionType;
}
