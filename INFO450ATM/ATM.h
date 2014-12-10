#ifndef ATM_H
#define ATM_H

#pragma once

#include <string>
#include "Customer.h"
#include "UI.h"
#include "Account.h"
#include "Database.h"
#include "Transaction.h"

using namespace std;


class ATM
{
	bool atmShutdown = false;
	string email = "";
	int pin = NULL;

public:
	ATM();
	~ATM();

	bool GetAtmShutdown();

	//ATM Functions
	bool login();
	void MainMenu();
	void performBalanceInquiry();
	void performWithdrawal();
	void performDeposit();
	int performTransfer();
	void showTransactionHistory();	
	void logoutCustomer();
	void shutdown();
	string GetDate();
};

#endif