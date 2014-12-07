#include "ATM.h"
#include <iostream>
#include "Database.h"
#include "Customer.h"
#include "UI.h"
#include <ctime>


using namespace std;

UI *ui = new UI();
Customer *customer;
Account *account;
Database *db = new Database();
int timestamp() {
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	cout << (now->tm_year + 1900) << '-'
		<< (now->tm_mon + 1) << '-'
		<< now->tm_mday
		<< endl;
}
// default ATM Constructor
ATM::ATM()
{
}

// default ATM Destructor
ATM::~ATM()
{
}

// login method
// we plan on it taking in the eMail AND the PIN before any authentication confirmation is done
bool ATM::login(string email, int PIN) {
	// stores the email addresss and PIN entered by the user	

	// prompts the User to enter their email
	ui->ShowLoginPrompt();
	cin >> email;

	ui->ClearBuffer();

	// prompts the user to enter their PIN, without clearing the LoginPrompt
	ui->ShowPINPrompt();
	cin >> PIN;

	ui->ClearBuffer();

#pragma region Authentication logic
	customer = db->getCustomer(email);

	// Test to see if a valid Customer was returned by the getCustomer()
	// function call above.
	if (customer->GetCustomerNumber() != 0)
	{
		if (customer->GetPIN() == PIN)
		{
			account = db->getAccount(customer->GetCustomerNumber());
			MainMenu();
			return true;
	}
	}
	else
		return false;
#pragma endregion
}

// MainMenu method
// uses a switch to determine what the user would like to do during this interaction.
void ATM::MainMenu() {


	// input from the user used to control the switch
	int actionToBePerformed = NULL;

	// shows a preconstructed MainMenu (this MainMenu method also clears the screen everytime it is called)
	// again for the shallow prototype justin jones is set to automatically appear as the user
	ui->ShowTransactionTypeMenu(customer->GetFirstName(), customer->GetLastName());
	cin >> actionToBePerformed;

	ui->ClearBuffer();

	// calls the users desired interaction based on the user input
	switch (actionToBePerformed)
	{
	case 1: withdraw(); break;
	case 2: deposit(); break;
	case 3: balance(); break;
	case 4: transfer(); break;
	case 5: history(); break;
	case 6: logout(); break;
	default: ui->ShowErrorMessage("Invalid menu choice! Please choose 1-6."); break;
	}
}

// withdraw method
// if the user selected a withdraw they will be taken to this screen
int ATM::withdraw() {
	// the amount the person would like to withdraw (increments of $20)
	int amountToWithdraw = NULL;

	// prints a preconstructed transaction amounts menu
	// has a clear screen function inside that clears everything that happened on the MainMenu
	ui->ShowTransactionAmountMenu("withdrawn");
	// takes in the amount the user would like to withdraw
	cin >> amountToWithdraw;

	ui->ClearBuffer();

	// again for the shallow prototype, there will only be success, 
	// so this screen will automatically be displayed next
	ui->ShowTransactionSuccessMessage();


	// recalls MainMenu, meaning the screen is cleared of everything
	// that happened during withdraw
	return 0;
}

// deposit method
// if the user selected deposit they will be taken to this screen
int ATM::deposit() {
	// the amount the person would like to deposit (increments of $20 for the shallow prototype)
	int amountToDeposit = NULL;

	// prints a precontructed transaction amounts menu
	// has a clear screen function inside that clears everything that happened on the MainMenu
	ui->ShowTransactionAmountMenu("deposited");
	// takes in the amount the user would like to deposit
	cin >> amountToDeposit;

	ui->ClearBuffer();
#pragma region Deposit logic
	//Logic for Deposit

	db->updateBalance(account->GetAccountNumber, amountToDeposit);
	//Will send the function the account number and the deposit amount
	//In case you're lazy, The updatebalance function will add the amount to deposit to the current balance and give you the updated balance

#pragma endregion
	// again for the shallow prototype, there will only be success, 
	// so this screen will automatically be displayed next
	
	db->createTransaction(account->GetAccountNumber, amountToDeposit, );
	ui->ShowTransactionSuccessMessage();


	// recalls MainMenu, meaning the screen is cleared of everything
	// that happened during withdraw
	return 0;
}

// transfer method
// if the user selected transfer they will be taken to this screen
int ATM::transfer() {
	// takes in the account the user would like to transfer money to and the amount to transfer
	char accountToTransferTo[50] = "NULL";
	int amountToTransfer = NULL;

	// prints a preconstructed transaction amounts menu (forces increments of $20 for shallow prototype)
	// has a clear screen function inside that clears everything that happened on the MainMenu
	ui->ShowTransactionAmountMenu("transfered");
	// takes in the amount the user would like to transfer
	cin >> amountToTransfer;

	ui->ClearBuffer();

	// asks the user for the email of the account to transfer money to
	cout << "Please enter the Account you would like to transfer to: ";
	// takes in the email of the account to transfer money to
	cin >> accountToTransferTo;
	
	ui->ClearBuffer();

	// again for the shallow prototype, there will only be success, 
	// so this screen will automatically be displayed next
	ui->ShowTransactionSuccessMessage();

	// recalls MainMenu, meaning the screen is cleared of everything
	// that happened during deposit
	return 0;
}

// history method
// if the user selected see transaction history, they will be taken to this screen
void ATM::history() {
	// clears the screen of the MainMenu
	ui->ClearScreen();
	// for the shallow prototype we determined we will want the table to look like:
	// Transaction #		Description				Date		Amount
	cout << "Transaction #\t\t Description\t\t\t\t Date\t\t Amount" << endl;

	// this will pause the screen so that the user can see what their previous transactions have been, and from where
	ui->PauseScreen();
	// when a key is pressed it will continue with the rest of history()
	ui->PressAnyKeyToContinue();

	// recalls MainMenu, meaning the screen is cleared of everything
	// that happened during history
}

// balance method
// if the user selected to see their balance, they will be taken to this screen
void ATM::balance() {
	// the amount the person has in their account, taken in from elsewhere
	int balance = NULL;

	string customerName = customer->GetFirstName() + " " + customer->GetLastName();

	ui->ShowAccountBalance(customerName, account->GetAccountBalance());	
}

void ATM::logout()
{
	// Logout procedure needs to be fleshed out
}

bool ATM::ValidateAmountInput(double amountEntered)
{
	double amountEntered;
	bool intervalOf20;

	intervalOf20 = (int)amountEntered % 20;
	if (intervalOf20)
	{
		return true;
	}
	else
	{
		ui->ShowErrorMessage("The amount input is not an interval of $20.00!");
		return false;
	}
}