#include "ATM.h"
#include <iostream>
#include "UI.h"

using namespace std;

// Function prototypes - Much of this behavior needs to be moved to the ATM object.
void MainMenu();
void login();
int withdraw();
int deposit();
int balance();
int transfer();
void history();
UI *ui = new UI();

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
void login() {
	// stores the email addresss and PIN entered by the user
	char eMail[50] = "NULL";
	int PIN = NULL;

	// prompts the User to enter their email
	ui->ShowLoginPrompt();
	cin >> eMail;
	/**************** CODE TO CLEAR THE INPUT BUFFER ****************
	****************************************************************/
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	// prompts the user to enter their PIN, without clearing the LoginPrompt
	ui->ShowPINPrompt();
	cin >> PIN;
	/**************** CODE TO CLEAR THE INPUT BUFFER ****************
	****************************************************************/
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	//instead of authentication, for now it just automatically takes you in to the main menu
	MainMenu();
}

// MainMenu method
// uses a switch to determine what the user would like to do during this interaction.
void MainMenu() {
	// input from the user used to control the switch
	int actionToBePerformed = NULL;

	// shows a preconstructed MainMenu (this MainMenu method also clears the screen everytime it is called)
	// again for the shallow prototype justin jones is set to automatically appear as the user
	ui->ShowTransactionTypeMenu("Justin", "Jones");
	cin >> actionToBePerformed;

	/**************** CODE TO CLEAR THE INPUT BUFFER ****************
	****************************************************************/
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	// calls the users desired interaction based on the user input
	switch (actionToBePerformed)
	{
	case 1: withdraw(); break;
	case 2: deposit(); break;
	case 3: balance(); break;
	case 4: transfer(); break;
	case 5: history(); break;
	case 6: login(); break;
	default: ui->ShowErrorMessage("Invalid menu choice! Please choose 1-6."); break;
	}
}

// withdraw method
// if the user selected a withdraw they will be taken to this screen
int withdraw() {
	// the amount the person would like to withdraw (increments of $20)
	int amountToWithdraw = NULL;

	// prints a preconstructed transaction amounts menu
	// has a clear screen function inside that clears everything that happened on the MainMenu
	ui->ShowTransactionAmountMenu("withdrawn");
	// takes in the amount the user would like to withdraw
	cin >> amountToWithdraw;
	/**************** CODE TO CLEAR THE INPUT BUFFER ****************
	****************************************************************/
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	// again for the shallow prototype, there will only be success, 
	// so this screen will automatically be displayed next
	ui->ShowTransactionSuccessMessage();


	// recalls MainMenu, meaning the screen is cleared of everything
	// that happened during withdraw
	MainMenu();
	return 0;
}

// deposit method
// if the user selected deposit they will be taken to this screen
int deposit() {
	// the amount the person would like to deposit (increments of $20 for the shallow prototype)
	int amountToDeposit = NULL;

	// prints a precontructed transaction amounts menu
	// has a clear screen function inside that clears everything that happened on the MainMenu
	ui->ShowTransactionAmountMenu("depositied");
	// takes in the amount the user would like to deposit
	cin >> amountToDeposit;
	/**************** CODE TO CLEAR THE INPUT BUFFER ****************
	****************************************************************/
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	// again for the shallow prototype, there will only be success, 
	// so this screen will automatically be displayed next
	ui->ShowTransactionSuccessMessage();

	// recalls MainMenu, meaning the screen is cleared of everything
	// that happened during withdraw
	MainMenu();
	return 0;
}

// transfer method
// if the user selected transfer they will be taken to this screen
int transfer() {
	// takes in the account the user would like to transfer money to and the amount to transfer
	char accountToTransferTo[50] = "NULL";
	int amountToTransfer = NULL;

	// prints a preconstructed transaction amounts menu (forces increments of $20 for shallow prototype)
	// has a clear screen function inside that clears everything that happened on the MainMenu
	ui->ShowTransactionAmountMenu("transfered");
	// takes in the amount the user would like to transfer
	cin >> amountToTransfer;
	/**************** CODE TO CLEAR THE INPUT BUFFER ****************
	****************************************************************/
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	// asks the user for the email of the account to transfer money to
	cout << "Please enter the Account you would like to transfer to: ";
	// takes in the email of the account to transfer money to
	cin >> accountToTransferTo;
	/**************** CODE TO CLEAR THE INPUT BUFFER ****************
	****************************************************************/
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	// again for the shallow prototype, there will only be success, 
	// so this screen will automatically be displayed next
	ui->ShowTransactionSuccessMessage();

	// recalls MainMenu, meaning the screen is cleared of everything
	// that happened during deposit
	MainMenu();
	return 0;
}

// history method
// if the user selected see transaction history, they will be taken to this screen
void history() {
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
	MainMenu();
}

// balance method
// if the user selected to see their balance, they will be taken to this screen
int balance() {
	// the amount the person has in their account, taken in from elsewhere
	int balance = NULL;

	// uses a preconstructed account balance screen to print the balance for the user
	// for the shallow prototype we already set a name and a balance
	ui->ShowAccountBalance("Justin Jones", 10000000000.23);

	// recalls MainMenu, meaning the screen is cleared of everything
	// that happened during balance
	MainMenu();
	return 0;
}