#ifndef ATM_H
#define ATM_H

#pragma once

#include <string>
#include "Customer.h"

using namespace std;

// I haven't yet thought about this class as I've 
// been focusing on the objects which are stored 
// in the database.

class ATM
{
public:
	ATM();
	~ATM();

	//ATM Functions
	bool login(string email, int PIN);
	void MainMenu();
	int withdraw();
	int deposit();
	int transfer();
	void history();
	void balance();
	void customerLogout();
	void ValidateAmountInput(double amountInput);
	void shutdown();
	string GetTimeStamp();
};

#endif