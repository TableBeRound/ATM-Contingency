#include "ATM.h"
#include <iostream>
#include <vector>

using namespace std;

// UI object used to interface with the customer
// This is necesary to keep the business logic 
// separate from the UI.
UI *ui = new UI();

// Here are the global Customer and Account objects for all ATM functions.
// This made more sense to me rather than passing these objects
// back and forth between the various functions.
Customer *customer;
Account *account;

// This database object is used to communicate with the embedded SQLite database.
Database *db = new Database();

// This vector is used to store all the transactions that the customer
// performs while they are logged in.  Updates to the AccountTransaction
// table are made once the user logs out.
std::vector<Transaction> collectionOfTransactions;

// This vector is used to store all the transfers that the customer
// performs while they are logged in.  Updates to the AccountTransfer
// table are made once the user logs out.
std::vector<Transfer> collectionOfTransfers;

// This vector is used to store those accounts which are sent a 
// transfer from the currently logged-in customer.
std::vector<Account *> collectionOfAccounts;

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

	// Get the customer data using the email address provided
	customer = db->getCustomer(email);

	// Test to see if a valid Customer was returned by the getCustomer()
	// function call above. A customer number of 0 is not possible...
	if (customer->GetCustomerNumber() != 0)
	{
		// If the PIN entered by the user matches the one that is stored
		// in the database, get the account information for that customer and 
		// return "true" so that the MainMenu is called (see the Source.cpp file)
		if (customer->GetPIN() == pin)
		{		
			// We've hard-coded a "C" here because we built the function with 
			// the idea that in the future customers could have more than one
			// type of account.
			account = db->getAccount(customer->GetCustomerNumber(), "C");
			return true;
		}
		else
			// Return false if the PINs do no match.
			return false;
	}
	else
		return false;
}

// The Main Menu uses a switch to determine what the user would like to do during this interaction.
void ATM::MainMenu() {

	bool userLogout = false;
	
	do{
		// This variable stores the integer returned by the UI's
		// ShowTransactionTypeMenu() function.  The integer is
		// used to determine what ATM-related action to perform.
		int actionToBePerformed = 0;		
		actionToBePerformed = ui->ShowTransactionTypeMenu(customer->GetFirstName(), customer->GetLastName());

		// Uses the result from above to call the function
		// related to the user's desired transaction.
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
			//ui->ClearBuffer();
			PerformTransfer();			
			break;
		case 5:
			//ShowTransactionHistory();
			cout << "Perform Transaction History" << endl << endl;
			system("pause");
			break;
		case 6: 
			LogoutCustomer();
			userLogout = true;			
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
	if (account->GetAccountBalance() >= amountToWithdraw)
	{
		// Create a new Transaction object and add it to the "batch" of transactions to process 
		// when the user chooses to log out.
		Transaction newWithdrawal = Transaction(account->GetAccountNumber(), amountToWithdraw, "W");
		collectionOfTransactions.push_back(newWithdrawal);

		// Add the amount of the new deposit to the account's balance
		accountBalance -= amountToWithdraw;
		account->SetAccountBalance(accountBalance);

		// Show the user that the transaction was a success.
		ui->ShowTransactionSuccessMessage();
	}
	else
		// If the user does not have sufficient funds to cover the withdrawal, display this error message.
		ui->ShowErrorMessage("Insufficient funds in this account!");
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
	Transaction newDeposit = Transaction(account->GetAccountNumber(), amountToDeposit, "D");
	collectionOfTransactions.push_back(newDeposit);

	// Add the amount of the new deposit to the account's balance
	accountBalance += amountToDeposit;
	account->SetAccountBalance(accountBalance);

	// Show the user that the transaction was a success.
	ui->ShowTransactionSuccessMessage();
}

// This logic executes if the user selected to make a transfer from the Main Menu
// A transfer is the movement of funds from one account to another.
void ATM::PerformTransfer() {

	// Variable declaration and initiation
	double currentBalanceOfSourceAccount = account->GetAccountBalance();
	int destinationAccountNumber = 0;
	double amountToTransfer = 0.0;

	// Get the number for the account which will be recieving the transfer and
	// use that number to retrieve that account's information - building an
	// Account object named destinationAccount.
	destinationAccountNumber = ui->ShowDestinationAccountPrompt();
	Account *destinationAccount = db->getAccount(destinationAccountNumber);
	
	if (destinationAccount->GetAccountNumber() != 0)
	{
		// Prints a preconstructed transaction amounts menu (forces increments of $20)
		// and stores the result of the user's choice in the amountToTransfer variable.
		amountToTransfer = ui->ShowTransactionAmountMenu("transferred");

		if (currentBalanceOfSourceAccount >= amountToTransfer)
		{
			// Create a new Transfer object and add it to the "batch" of transfers to process 
			// when the user chooses to log out.
			Transfer newTransfer = Transfer(account->GetAccountNumber(), destinationAccountNumber, amountToTransfer);
			collectionOfTransfers.push_back(newTransfer);

			// Subtract the amount of the new transfer from the "source" account's balance
			currentBalanceOfSourceAccount -= amountToTransfer;
			account->SetAccountBalance(currentBalanceOfSourceAccount);

			/*ui->ClearScreen();
			cout << "Source Acct Info:\n\n"
				<< "Acct Number: " + std::to_string(account->GetAccountNumber()) << endl
				<< "Acct Balance: " + std::to_string(account->GetAccountBalance());
			system("pause");*/

			// And add the amount of the new transfer to the "destination" account's balance
			double BalOfDestAcct = destinationAccount->GetAccountBalance();
			BalOfDestAcct += amountToTransfer;
			destinationAccount->SetAccountBalance(BalOfDestAcct);

			// Add the destinationAccount to the list of accounts to update when the user logs out
			collectionOfAccounts.push_back(destinationAccount);

			/*cout << "Destination Acct Info:\n\n"
				<< "Acct Number: " + std::to_string(destinationAccount->GetAccountNumber()) << endl
				<< "Acct Balance: " + std::to_string(destinationAccount->GetAccountBalance());
			system("pause");*/

			// Show the user that the transaction was a success.
			ui->ShowTransactionSuccessMessage();
		}
		else
			// If the user does not have sufficient funds to cover the withdrawal, display this error message.
			ui->ShowErrorMessage("Insufficient funds in this account!");
	}
	else
	{
		ui->ShowErrorMessage("That is not a valid account number.");
	}	
}

// This logic executes if the user selected to view their transaction history from the Main Menu
void ATM::ShowTransactionHistory() 
{
	
}

// logoutCustomer() writes all the new transactions (if any) to the database
// and performs any other house-cleaning routines.
void ATM::LogoutCustomer()
{
	// Move through the collection of Transactions and write each one to the database.
	// This could be more efficient if we employed a batch process rather than writing
	// each transaction one at a time.
	for (unsigned int i = 0; i < collectionOfTransactions.size(); i++)
	{
		db->createTransaction(collectionOfTransactions[i].GetAccountNumber(),
							  collectionOfTransactions[i].GetTransactionAmount(),
							  collectionOfTransactions[i].GetTransactionType());
	}	

	// Move through the collection of Transfers and write each one to the database.
	// This could be more efficient if we employed a batch process rather than writing
	// each transaction one at a time.
	for (unsigned int i = 0; i < collectionOfTransfers.size(); i++)
	{
		db->createTransfer(collectionOfTransfers[i].GetAccountNumber(),
			collectionOfTransfers[i].GetDestinationAccountNumber(),
			collectionOfTransfers[i].GetTransactionAmount());
	}

	// Move through the collection of Accounts which have received transfers from this 
	// customer and update each of their balances.
	for (unsigned int i = 0; i < collectionOfAccounts.size(); i++)
	{
		db->updateBalance(collectionOfAccounts[i]->GetAccountNumber(), collectionOfAccounts[i]->GetAccountBalance());
	}

	// Update the currently logged-in user's account information stored in the database
	// to refelct the account's new balance after all the transactions have taken place.
	db->updateBalance(account->GetAccountNumber(), account->GetAccountBalance());

	// Clear out the vectors keeping track of the transactions, transfers, and accounts.
	collectionOfTransactions.clear();
	collectionOfTransfers.clear();
	collectionOfAccounts.clear();
}