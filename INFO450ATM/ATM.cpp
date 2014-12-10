#include "ATM.h"
#include <iostream>
#include <vector>

using namespace std;

UI *ui = new UI();
Customer *customer;
// Account has been filled with dummy data while database is being worked on.
Account *account = new Account(1, 2, 'C', 100.00);
Database *db = new Database();
std::vector<Transaction> collectionOfTransactions;

// default ATM Constructor
ATM::ATM()
{
}

// default ATM Destructor
ATM::~ATM()
{
}

bool ATM::Login() {
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
			// database lookup for account should happen here
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
			PerformWithdrawal();
			break;
		case 2:
			PerformDeposit();
			break;
		case 3:
			PerformBalanceInquiry();
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

// This logic executes if the user selected to see their balance from the Main Menu
void ATM::PerformBalanceInquiry() {

	// Build a string to show the customer's name.
	string customerName = customer->GetFirstName() + " " + customer->GetLastName();

	// Show the current balance of the account.
	ui->ShowAccountBalance(customerName, account->GetAccountBalance());
}

// This logic executes if the user selected to make a withdrawal from the Main Menu
void ATM::PerformWithdrawal() 
{
	// Get the current balance of the account
	double accountBalance = account->GetAccountBalance();

	// At this point, the user will be shown the transaction menu where they 
	// will make a selection.  The amount which they would like to withdraw
	// is then returned and stored in the "amountToWithdraw" variable declared below.
	double amountToWithdraw = ui->ShowTransactionAmountMenu("withdrawn");

	// Check to see if the customer has the available funds to perform the withdrawal
	if (accountBalance >= amountToWithdraw)
	{
		// Create a new Transaction object and add it to the "batch" of transactions to process 
		// when the user chooses to log out.
		Transaction newWithdrawal = Transaction(account->GetAccountNumber(), amountToWithdraw, "W", GetDate());
		collectionOfTransactions.push_back(newWithdrawal);

		// Add the amount of the new deposit to the account's balance
		accountBalance -= amountToWithdraw;
		account->SetAccountBalance(accountBalance);

		// Show the user that the transaction was a success.
		ui->ShowTransactionSuccessMessage();
	}
	else
		// If the user does not have sufficient funds to cover the withdrawal, display this error message.
		ui->ShowErrorMessage("There are insufficient funds in this account to perform a withdrawal of that amount.");
}

// This logic executes if the user selected to make a deposit from the Main Menu
void ATM::PerformDeposit() 
{
	double accountBalance = account->GetAccountBalance();
	// At this point, the user will be shown the transaction menu where they 
	// will make a selection.  The amount which they would like to deposit
	// is then returned and stored in the "amountToDeposit" variable declared below.
	double amountToDeposit = ui->ShowTransactionAmountMenu("deposited");

	// Create a new Transaction object and add it to the "batch" of transactions to process 
	// when the user chooses to log out.
	Transaction newDeposit = Transaction(account->GetAccountNumber(), amountToDeposit, "W", GetDate());
	collectionOfTransactions.push_back(newDeposit);

	// Add the amount of the new deposit to the account's balance
	accountBalance += amountToDeposit;
	account->SetAccountBalance(accountBalance);

	// Show the user that the transaction was a success.
	ui->ShowTransactionSuccessMessage();
}

// This logic executes if the user selected to make a transfer from the Main Menu
int ATM::PerformTransfer() {
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

// This logic executes if the user selected to view their transaction history from the Main Menu
void ATM::ShowTransactionHistory() 
{
	
}

// logoutCustomer writes all the new transactions (if any) to the database
// and performs any other house-cleaning routines.
void ATM::LogoutCustomer()
{
	// Logout procedure needs to be fleshed out
}

// Returns a timestamp for all database transactions
string ATM::GetDate()
{
	return " ";
}