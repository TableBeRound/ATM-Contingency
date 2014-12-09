#include "ATM.h"
#include <iostream>
#include <ctime>

using namespace std;

UI *ui = new UI();
Customer *customer;
Account *account;
Database *db = new Database();

// default ATM Constructor
ATM::ATM()
{
}

// default ATM Destructor
ATM::~ATM()
{
}

bool ATM::login() {
	// stores the email addresss and PIN entered by the user	

	// prompts the User to enter their email
	email = ui->ShowLoginPrompt();
	ui->ClearBuffer();

	// prompts the user to enter their PIN, without clearing the LoginPrompt
	pin = ui->ShowPINPrompt();
	ui->ClearBuffer();

#pragma region Authentication logic
	customer = db->getCustomer(email);

	// Test to see if a valid Customer was returned by the getCustomer()
	// function call above.
	if (customer->GetCustomerNumber() != 0)
	{
		if (customer->GetPIN() == pin)
		{		
			//account = db->getAccount(customer->GetCustomerNumber());
			return true;
		}
		else
			return false;
	}
	else
		return false;
#pragma endregion

}

// MainMenu method
// uses a switch to determine what the user would like to do during this interaction.
void ATM::MainMenu() {

	bool userLogout = false;
	
	do{
		// input from the user used to control the switch			
		int actionToBePerformed = 0;
		
		actionToBePerformed = ui->ShowTransactionTypeMenu(customer->GetFirstName(), customer->GetLastName());

		// calls the users desired interaction based on the user input
		switch (actionToBePerformed)
		{
		case 1:
			//withdraw();
			cout << "Perform Withdrawal" << endl << endl;
			system("pause");
			break;
		case 2:
			performDeposit();
			break;
		case 3:
			//balance();
			cout << "Perform Balance Inquiry" << endl << endl;
			system("pause");
			break;
		case 4:
			//transfer();
			cout << "Perform Transfer" << endl << endl;
			system("pause");
			break;
		case 5:
			//history();
			cout << "Perform Transaction History" << endl << endl;
			system("pause");
			break;
		case 6: userLogout = true;			
			break;
		}
	} while (!userLogout);
}

// withdraw method
// if the user selected a withdraw they will be taken to this screen
int ATM::performWithdrawal() {
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
// SHOULD THIS FUNCTION RETURN A TRANSACTION OBJECT? - we could build a growing
// list of transactions which are processed once a user logs out.
void ATM::performDeposit() {

	// At this point, the user will be shown the transaction menu where they 
	// will make a selection.  The amount which they would like to deposit
	// is then returned and stored in the "amountToDeposit" variable declared below.
	double amountToDeposit = ui->ShowTransactionAmountMenu("deposited");
	// takes in the amount the user would like to deposit

	cout << "\n\nAmount to be deposited: " << std::to_string(amountToDeposit) << "\n\n";
	system("pause");
}

// transfer method
// if the user selected transfer they will be taken to this screen
int ATM::performTransfer() {
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

void ATM::customerLogout()
{
	// Logout procedure needs to be fleshed out
}

void ATM::ValidateAmountInput(double amountEntered)
{
	if ((int)amountEntered % 20 > 0)
	{
		ui->ShowErrorMessage("The amount input is not an interval of $20.00!");
	}
}

string ATM::GetTimeStamp()
{
	return " ";
}