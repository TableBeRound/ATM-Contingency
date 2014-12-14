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
Customer *customer = new Customer();
Account *account;

// This database object is used to communicate with the embedded SQLite database.
Database *db = new Database();

// This vector is used to store Page objects which facilitate the
// display of the transactionHistory of an account.
std::vector<Page> transactionHistory;

// This vector is used to store Page objects which facilitate the
// display of the transferHistory of an account.
std::vector<Page> transferHistory;

// default ATM Constructor
ATM::ATM()
{
}

// default ATM Destructor
ATM::~ATM()
{
}

bool ATM::Login() {

	// Prompt the user: Are you a returning customer or a new customer?
	// Store the answer and determine how to proceed below.
	bool returningCustomer = ui->ShowReturningCustomerNewCustomerPrompt();

	// If they are a returning customer, proceed with normal login procedure.
	if (returningCustomer)
	{
		// prompts the User to enter their email
		email = ui->ShowLoginPrompt();

		// prompts the user to enter their PIN, without clearing the LoginPrompt
		pin = ui->ShowPINPrompt();

		// Get the customer data from the database using the email address provided
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

				// Check to see if the account is "ACTIVE" or "INACTIVE".  
				// If it's active, proceed.
				if (account->GetAccountStatus() == "ACTIVE")
				{
					return true;
				}
				// If it's not active, give an error message and proceed no further.
				else
				{
					ui->ShowErrorMessage("This account is currently inactive!");
					return false;
				}				
			}
			// Return false if the PINs do no match.
			else				
				return false;
		}
		// If a bad customer email was given and the database could
		// not build a customer object from the data, it should return 
		// a customer number of zero.  Proceed no further.
		else
			return false;
	}
	// If the user is not a returning customer, they must 
	// have chosen to create a new customer profile.
	else
	{
		CreateNewCustomer();
		return false;
	}
}

void ATM::CreateNewCustomer()
{
	int keyboardhit = 0;

	ui->ShowCreateNewCustomerProfileForm(customer);
	// waits for the user to confirm if they want to use the information they already input
	// if they confirm using it, and the email address or pin are not in a proper format
	// then it will throw an error message and allow them to try again
	if (!IsValidEmail(customer->GetEmailAddress()) || !IsValidPin(customer->GetPIN()))
	{
		ui->ShowErrorMessage("Invalid Email or PIN! Please try again.");
		CreateNewCustomer();
	}
	// if the input that was confirmed had a proper email address and pin
	// then the account is created
	else
	{
		// everything below this line is original
		// ***************************************************
		//ui->ShowCreateNewCustomerProfileForm(customer);
		db->createCustomer(customer->GetLastName(), customer->GetFirstName(), customer->GetEmailAddress(), customer->GetPIN());
		customer = db->getCustomer(customer->GetEmailAddress());
		db->createAccount(customer->GetCustomerNumber(), "C");
		// ***************************************************
		// everything above this line is original
	}
}

// function used to check if the PIN entered is between 4 and 6 digits
bool ATM::IsValidPin(int pin)
{
	if (pin >= 1000 && pin <= 999999)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// This was taken from "how do i check a user input string with email format"
// on stackoverflow.com http://stackoverflow.com/questions/14913341/how-do-i-check-a-user-input-string-with-email-format
// this really only checks that it is a normal style email of "email@company.com"
// used http://www.cplusplus.com/reference/string/string/find_first_of/ to learn 
// the context of find_first_of()
bool ATM::IsValidEmail(string const& email)
{
	// Searches for the 1st @ in the input string.
	// The 1 means it starts from position 1 in the string.
	// This will prevent an email with now "username" field like @company.com from working
	// (an unsigned int-->)size_t locationOfAT is the numerical location
	// in the string email that the charcter @ is
	size_t locationOfAT = email.find_first_of('@', 1);
	// returns true as long as email.find_first_of() found an @ in the string
	// AND as long as a . is found, and it is at some location after the @
	return locationOfAT != std::string::npos && email.find_first_of('.', locationOfAT) != std::string::npos;
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
			PerformTransfer();			
			break;
		case 5:
			ShowTransactionHistory();
			break;
		case 6:
			ShowTransferHistory();
			break;
		case 7: 
			ManageAccount();
			break;
		case 8:
			LogoutCustomer();
			userLogout = true;
			break;
		}
	} while (!userLogout && account->GetAccountStatus() == "ACTIVE");
}

// This logic executes if the user selected to see their balance from the Main Menu
void ATM::PerformBalanceInquiry() {

	// Build a string to show the customer's name.
	string customerName = customer->GetFirstName() + " " + customer->GetLastName();

	// Show the current balance of the account.
	ui->ShowAccountBalance(customerName, account->GetAccountNumber(), account->GetAccountBalance());
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
	if (amountToWithdraw != 0 && account->GetAccountBalance() >= amountToWithdraw)
	{
		// Subtract the amount of the withdrawal from the account's balance
		accountBalance -= amountToWithdraw;
		account->SetAccountBalance(accountBalance);		

		// Record the transaction in the database.
		db->createTransaction(account->GetAccountNumber(), amountToWithdraw, "W");
		ui->ShowTransactionSuccessMessage();
	}
	else if (amountToWithdraw != 0 && account->GetAccountBalance() < amountToWithdraw)
	{
		// If the user does not have sufficient funds to cover the withdrawal, display this error message.
		ui->ShowErrorMessage("Insufficient funds in this account!");
	}		
}

// This logic executes if the user selected to make a deposit from the Main Menu
void ATM::PerformDeposit() 
{
	double accountBalance = account->GetAccountBalance();
	// At this point, the user will be shown the transaction menu where they 
	// will make a selection.  The amount which they would like to deposit
	// is then returned and stored in the "amountToDeposit" variable declared below.
	double amountToDeposit = ui->ShowTransactionAmountMenu("deposited");

	if (amountToDeposit != 0)
	{
		// Add the amount of the new deposit to the account's balance
		accountBalance += amountToDeposit;
		account->SetAccountBalance(accountBalance);

		// Record the transaction in the database.
		db->createTransaction(account->GetAccountNumber(), amountToDeposit, "D");
		ui->ShowTransactionSuccessMessage();
	}	
}

// This logic executes if the user selected to make a transfer from the Main Menu
// A transfer is the movement of funds from one account to another.
void ATM::PerformTransfer() {

	// Variable declaration and initiation
	double currentBalanceOfSourceAccount = account->GetAccountBalance();
	string destCustomerEmail = "";
	double amountToTransfer = 0.0;

	// Get the number for the account which will be recieving the transfer and
	// use that number to retrieve that account's information - building an
	// Account object named destinationAccount.
	destCustomerEmail = ui->ShowDestinationAccountPrompt();
	Customer *destinationCustomer = db->getCustomer(destCustomerEmail);
		
	if ((destinationCustomer->GetCustomerNumber() != 0) && (destCustomerEmail != "EscKeyPresedInShowDestAcctPrompt") && (destCustomerEmail != customer->GetEmailAddress()))
	{
		Account *destinationAccount = db->getAccount(destinationCustomer->GetCustomerNumber(), "C");
		// Prints a preconstructed transaction amounts menu (forces increments of $20)
		// and stores the result of the user's choice in the amountToTransfer variable.
		amountToTransfer = ui->ShowTransactionAmountMenu("transferred");

		if (currentBalanceOfSourceAccount >= amountToTransfer)
		{
			// Subtract the amount of the new transfer from the "source" account's balance
			currentBalanceOfSourceAccount -= amountToTransfer;
			account->SetAccountBalance(currentBalanceOfSourceAccount);
						
			// And add the amount of the new transfer to the "destination" account's balance
			double BalOfDestAcct = destinationAccount->GetAccountBalance();
			BalOfDestAcct += amountToTransfer;
			destinationAccount->SetAccountBalance(BalOfDestAcct);
						
			// Update the Destination Account's Balance
			db->updateBalance(destinationAccount->GetAccountNumber(), destinationAccount->GetAccountBalance());

			// Update the Transfer Table in the database
			db->createTransfer(account->GetAccountNumber(), destinationAccount->GetAccountNumber(), amountToTransfer);

			// Show that the transaction was a success
			ui->ShowTransactionSuccessMessage();

			delete destinationAccount;
		}
		else
			// If the user does not have sufficient funds to cover the withdrawal, display this error message.
			ui->ShowErrorMessage("Insufficient funds in this account!");
	}
	else if (destinationCustomer->GetCustomerNumber() == 0 && destCustomerEmail != "EscKeyPresedInShowDestAcctPrompt")
	{
		ui->ShowErrorMessage("No account exists for that email address.");
	}	
	else if (destCustomerEmail == customer->GetEmailAddress())
	{
		ui->ShowErrorMessage("Cannot transfer to an account while it is being used.");
	}

	delete destinationCustomer;
}

// This logic executes if the user selected to view their TRANSACTION history from the Main Menu
void ATM::ShowTransactionHistory() 
{
	db->populateTransactionHistory(account->GetAccountNumber(), &transactionHistory);
	ui->ShowTransactionHistory(transactionHistory, customer->GetFirstName(), customer->GetLastName());	
	transactionHistory.clear();
}

// This logic executes if the user selected to view their TRANSFER history from the Main Menu
void ATM::ShowTransferHistory()
{	
	db->populateTransferHistory(account->GetAccountNumber(), &transferHistory);
	ui->ShowTransferHistory(transferHistory, customer->GetFirstName(), customer->GetLastName());
	transferHistory.clear();
}

// This logic executes if the user selected to manage their account from the Main Menu
void ATM::ManageAccount()
{
	// Call a UI function which displays a prompt to change 
	// the account status and returns a boolean value.
	bool changeStatus = ui->ShowChangeAccountStatusPrompt();
	// If the boolean value is true, set the status of the 
	// account to INACTIVE and update the database.
	if(changeStatus)
	{
		account->SetAccountStatus("INACTIVE");
		db->updateStatus(account->GetAccountNumber(), account->GetAccountStatus());
	}
}

// logoutCustomer() writes all the new transactions (if any) to the database
// and performs any other house-cleaning routines.
void ATM::LogoutCustomer()
{
	// Update the currently logged-in user's account information stored in the database
	// to refelct the account's new balance after all the transactions have taken place.
	db->updateBalance(account->GetAccountNumber(), account->GetAccountBalance());

	// Clear out the vectors keeping track of the "pages" of the account's histories.	
	transactionHistory.clear();
	transferHistory.clear();
}

// This function simply cleans up any pointers that would
// otherwise be left lying around after shutdown.
void ATM::ShutdownATM()
{
	delete customer;
	delete account;
	delete ui;
	delete db;
}