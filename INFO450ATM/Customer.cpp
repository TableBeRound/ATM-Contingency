#include "Customer.h"


Customer::Customer()
{
}

Customer::Customer(int custNum, string lastName, string firstName, string emailAddress, int pin)
{
	this->_customerNumber = custNum;	
	this->_custLastName = lastName;
	this->_custFirstName = firstName;	
	this->_emailAddress = emailAddress;
	this->_PIN = pin;
}

Customer::~Customer()
{
}

//Get Functions
int Customer::GetCustomerNumber()
{
	return this->_customerNumber;
}

string Customer::GetEmailAddress()
{
	return this->_emailAddress;
}

string Customer::GetFirstName()
{
	return this->_custFirstName;
}

string Customer::GetLastName()
{
	return this->_custLastName;
}

int Customer::GetPIN()
{
	return this->_PIN;
}

void Customer::OpenNewAccount(){

}

void Customer::ViewListOfAccounts(){

}

void Customer::MakeDeposit(float depositAmount){

}

void Customer::MakeWithdrawal(float withdrawalAmount){

}
