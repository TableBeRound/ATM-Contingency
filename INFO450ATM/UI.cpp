#include "UI.h"
#include <iostream>
#include <iomanip>
#include "Windows.h"
#include "Conio.h"

using namespace std;

// Default constructor
UI::UI()
{
}

// Default destructor
UI::~UI()
{
}

// Display returning customer/new customer prompt
bool UI::ShowReturningCustomerNewCustomerPrompt()
{
	string select1 = "*";
	string select2 = " ";
	int keyboardHit = 0;

	while (keyboardHit != KEY_ENTER)
	{
		this->ClearScreen();
		cout << endl
			<< "\t\t\t    ***********************" << endl
			<< "\t\t\t    * Welcome to DAT Bank *" << endl
			<< "\t\t\t    ***********************" << endl
			<< endl
			<< endl
			<< " Are you a returning customer?" << endl
			<< endl
			<< "\t[" << select1 << "] 1) Returning customer" << endl   //<---- Choice #1
			<< "\t[" << select2 << "] 2) New customer" << endl;        //<---- Choice #2

		// Get keyboard input from the customer
		keyboardHit = _getch();

		// This switch moves the asterisk amongst the menu
		// items depending on what key has been hit
		switch (keyboardHit)
		{
		case KEY_DOWN:
			if (select1 == "*")
			{
				select1 = " ";
				select2 = "*";
			}
			else if (select2 == "*")
			{
				select2 = " ";
				select1 = "*";
			}			
			break;

		case KEY_UP:
			if (select1 == "*")
			{
				select1 = " ";
				select2 = "*";
			}
			else if (select2 == "*")
			{
				select2 = " ";
				select1 = "*";
			}
			break;
		}
	}

	// After the Enter Key has been pressed, determine
	// what selection was made by which variable has 
	// the asterisk assigned to it.
	if (select1 == "*")
	{
		return true;
	}
	else 
	{
		return false;
	}		
}

// Display standard login to the user
string UI::ShowLoginPrompt()
{
	string emailInput = "";

	this->ClearScreen();
	cout << endl
		<< "\t\t\t    ***********************" << endl
		<< "\t\t\t    * Welcome to DAT Bank *" << endl
		<< "\t\t\t    ***********************" << endl
		<< endl
		<< endl
		<< " Please enter your email: ";
	cin >> emailInput;
	this->ClearBuffer();

	return emailInput;
}

void UI::ShowCreateNewCustomerProfileForm(Customer *cust)
{
	bool inputValid = false;
	int keyboardHit = 0;
	string firstName= "";
	string lastName = "";
	string emailAddress = "";
	int pin = 0;

	while (!inputValid)
	{
		this->ClearScreen();
		cout << endl << "\t\t\t  Create a New Customer Account"
			<< endl << endl << endl << endl
			<< "  Please enter your information below." << endl << endl << endl
			<< "     First Name: ";
		cin >> firstName;
		this->ClearBuffer();
		cout << "     Last Name: ";
		cin >> lastName;
		this->ClearBuffer();
		cout << "     Email Address: ";
		cin >> emailAddress;
		this->ClearBuffer();
		cout << "     PIN: ";
		cin >> pin;
		this->ClearBuffer();
		cout << endl << endl << endl 
			<< "  Please review the information entered above." << endl		    
			<< endl << endl << endl
			<< "  Is this information correct? (Press \"Y\" for Yes and \"N\" for No)" << endl << endl
			<< endl << endl
			<< "  Press the Escape key to cancel.";
		keyboardHit = _getch();
		switch (keyboardHit)
		{
			// 121 is the integer returned by _getch() when the "Y" key is pressed on the keyboard
		case 121:
			inputValid = true;
			break;
		case KEY_ESC:
			inputValid = true;
			break;
		default:
			inputValid = false;
			break;
		}
	}
	if (keyboardHit == KEY_ESC)
	{
		this->ClearScreen();
		cout << "\n\n\n\n\t\t\t Account Creation Cancelled!\n\n";
	}
	else
	{
		cust->SetFirstName(firstName);
		cust->SetLastName(lastName);
		cust->SetEmailAddress(emailAddress);
		cust->SetPIN(pin);
		this->ClearScreen();		
		cout << "\n\n\n\n\t\t\t Account Creation Successful!\n\n";
	}
}

// Prompt the user to enter a PIN
int UI::ShowPINPrompt()
{
	int pinInput = NULL;

	cout << endl << endl
		<< " Please enter PIN: ";
	cin >> pinInput;
	this->ClearBuffer();

	return pinInput;
}

// Display the menu of possible transactions to the user as selections 1-6
int UI::ShowTransactionTypeMenu(string custFirstName, string custLastName)
{
	char select1 = '*';
	char select2 = ' ';
	char select3 = ' ';
	char select4 = ' ';
	char select5 = ' ';
	char select6 = ' ';
	char select7 = ' ';
	char select8 = ' ';
	int keyboardHit = 0;
	int userSelection = 0;

	// As long as the user hasn't hit the Enter key loop
	while (keyboardHit != KEY_ENTER)
	{
		this->ClearScreen();
		cout << endl
			<< "\t\t\t    Welcome " + custFirstName + " " + custLastName + "!"
			<< endl << endl
			<< "\n\n  Use the UP/DOWN arrow keys to make a selection (1-6):" << endl
			<< endl << endl
			<< "\t[" << select1 << "] 1) Make a withdrawal" << endl          //<---- Choice #1
			<< "\t[" << select2 << "] 2) Make a deposit" << endl             //<---- Choice #2
			<< "\t[" << select3 << "] 3) Check account balance" << endl      //<---- Choice #3
			<< "\t[" << select4 << "] 4) Make a transfer" << endl            //<---- Choice #4
			<< "\t[" << select5 << "] 5) See Transaction History" << endl	 //<---- Choice #5
			<< "\t[" << select6 << "] 6) See Transfer History" << endl       //<---- Choice #6
			<< "\t[" << select7 << "] 7) Manage Account" << endl             //<---- Choice #7
			<< "\t[" << select8 << "] 8) Logout" << endl                     //<---- Choice #7
			<< endl;

		// Get keyboard input from the customer
		keyboardHit = _getch();

		// This switch moves the asterisk amongst the menu
		// items depending on what key has been hit
		switch (keyboardHit)
		{
		case KEY_DOWN:
			if (select1 == '*')
			{
				select1 = ' ';
				select2 = '*';
			}
			else if (select2 == '*')
			{
				select2 = ' ';
				select3 = '*';
			}
			else if (select3 == '*')
			{
				select3 = ' ';
				select4 = '*';
			}
			else if (select4 == '*')
			{
				select4 = ' ';
				select5 = '*';
			}
			else if (select5 == '*')
			{
				select5 = ' ';
				select6 = '*';
			}
			else if (select6 == '*')
			{
				select6 = ' ';
				select7 = '*';
			}
			else if (select7 == '*')
			{
				select7 = ' ';
				select8 = '*';
			}
			else if (select8 == '*')
			{
				select8 = ' ';
				select1 = '*';
			}
			break;

		case KEY_UP:
			if (select1 == '*')
			{
				select1 = ' ';
				select8 = '*';
			}
			else if (select2 == '*')
			{
				select2 = ' ';
				select1 = '*';
			}
			else if (select3 == '*')
			{
				select3 = ' ';
				select2 = '*';
			}
			else if (select4 == '*')
			{
				select4 = ' ';
				select3 = '*';
			}
			else if (select5 == '*')
			{
				select5 = ' ';
				select4 = '*';
			}
			else if (select6 == '*')
			{
				select6 = ' ';
				select5 = '*';
			}
			else if (select7 == '*')
			{
				select7 = ' ';
				select6 = '*';
			}
			else if (select8 == '*')
			{
				select8 = ' ';
				select7 = '*';
			}
			break;
		}
	}

	// After the Enter Key has been pressed, determine
	// what selection was made by which variable has 
	// the asterisk assigned to it.
	if (select1 == '*')
	{
		userSelection = 1;
	}
	else if (select2 == '*')
	{
		userSelection = 2;
	}
	else if (select3 == '*')
	{
		userSelection = 3;
	}
	else if (select4 == '*')
	{
		userSelection = 4;
	}
	else if (select5 == '*')
	{
		userSelection = 5;
	}
	else if (select6 == '*')
	{
		userSelection = 6;
	}
	else if (select7 == '*')
	{
		userSelection = 7;
	}
	else if (select8 == '*')
	{
		userSelection = 8;
	}

	// Return the value of the selection determined by the above if statement.
	keyboardHit = NULL;
	return userSelection;
}

// Display the menu of possible transactions amounts to the user.
double UI::ShowTransactionAmountMenu(char *actionToBePerformed)
{
	char amount1 = '*';
	char amount2 = ' ';
	char amount3 = ' ';
	char amount4 = ' ';
	char amount5 = ' ';
	double transactionAmount = 0;
	int keyboardHit = NULL;

	while (keyboardHit != KEY_ENTER && keyboardHit != KEY_ESC)
	{
		this->ClearScreen();
		cout << endl 
			<< "\t\t   Please select amount to be " << actionToBePerformed << ":"
			<< endl << endl << endl << endl
			<< "  Use the UP/DOWN arrow keys to move the selector (*):" << endl
			<< endl << endl
			<< "\t[" << amount1 << "] 1) $20" << endl      //<---- Choice #1
			<< "\t[" << amount2 << "] 2) $40" << endl      //<---- Choice #2
			<< "\t[" << amount3 << "] 3) $60" << endl      //<---- Choice #3
			<< "\t[" << amount4 << "] 4) $80" << endl      //<---- Choice #4
			<< "\t[" << amount5 << "] 5) $100" << endl	  //<---- Choice #5			
			<< endl << endl  
			<< "  Press Enter to make your selection."
			<< endl << endl << endl << endl << endl << endl << endl
			<< "  Press Escape to return to the Main Menu.";

		keyboardHit = _getch();

		switch (keyboardHit)
		{
		case KEY_DOWN:
			if (amount1 == '*')
			{
				amount1 = ' ';
				amount2 = '*';
			}
			else if (amount2 == '*')
			{
				amount2 = ' ';
				amount3 = '*';
			}
			else if (amount3 == '*')
			{
				amount3 = ' ';
				amount4 = '*';
			}
			else if (amount4 == '*')
			{
				amount4 = ' ';
				amount5 = '*';
			}
			else if (amount5 == '*')
			{
				amount5 = ' ';
				amount1 = '*';
			}
			break;

		case KEY_UP:
			if (amount1 == '*')
			{
				amount1 = ' ';
				amount5 = '*';
			}
			else if (amount2 == '*')
			{
				amount2 = ' ';
				amount1 = '*';
			}
			else if (amount3 == '*')
			{
				amount3 = ' ';
				amount2 = '*';
			}
			else if (amount4 == '*')
			{
				amount4 = ' ';
				amount3 = '*';
			}
			else if (amount5 == '*')
			{
				amount5 = ' ';
				amount4 = '*';
			}
		}
	}

	if (keyboardHit == KEY_ENTER)
	{
		if (amount1 == '*')
		{
			transactionAmount = 20;
		}
		else if (amount2 == '*')
		{
			transactionAmount = 40;
		}
		else if (amount3 == '*')
		{
			transactionAmount = 60;
		}
		else if (amount4 == '*')
		{
			transactionAmount = 80;
		}
		else if (amount5 == '*')
		{
			transactionAmount = 100;
		}
	}
	
	return transactionAmount;
}

// Display an area for the customer to input the destination account number for making a transfer
string UI::ShowDestinationAccountPrompt()
{
	string email = "";
	bool inputValid = false;
	int keyboardHit = 0;

	while (!inputValid && keyboardHit != KEY_ESC)
	{
		this->ClearScreen();
		cout << endl << "\t\t\t  Transfer Funds to Another Account"
			<< endl  << endl << endl << endl
	        << "  Please enter the EMAIL ADDRESS of the account you would like to transfer to." << endl << endl << endl
			<< "  Destination Account: ";
		cin >> email;
		this->ClearBuffer();
		cout << endl << endl << endl << endl
			<< "\t  You entered: " + email 
			<< endl << endl << endl << endl << endl << endl;
		cout << "  Is this correct? (Press Y for \"Yes\" and N for \"No\")" << endl << endl
			<< endl << endl  
			<< "  Press the Escape key to return to the Main Menu.";
		keyboardHit = _getch();
		switch (keyboardHit)
		{
		// 121 is the integer returned by _getch() when the "Y" key is pressed on the keyboard
		case 121:
			inputValid = true;
			break;
		case KEY_ESC:
			inputValid = true;
			email = "EscKeyPresedInShowDestAcctPrompt";
			break;
		default:
			inputValid = false;
			break;
		}
	}
		
	return email;
}

// Display the menu of possible transactions amounts to the user.
void UI::ShowAccountBalance(string custName, int acctNum, double acctBalance)
{
	this->ClearScreen();
	cout << endl
		<< "\t\t\t\t*******************" << endl
		<< "\t\t\t\t* Current Balance *" << endl
		<< "\t\t\t\t*******************" << endl
		<< endl << endl << endl
		<< " " + custName << endl << endl
		<< "     Account #" + std::to_string(acctNum) + " (Checking): $" << std::fixed << std::setprecision(2) << acctBalance
		<< endl << endl << endl << endl << endl
		<< endl << endl << endl << endl << endl
		<< endl << endl << endl;
	this->PressAnyKeyToContinue();
}

// Transaction Success - feedback to the user tha something actually happened
void UI::ShowTransactionSuccessMessage()
{
	this->ClearScreen();
	cout << endl
		<< "\t\t\t   ***********************" << endl
		<< "\t\t\t   * Transaction Success *" << endl
		<< "\t\t\t   ***********************" << endl
		<< endl << endl
		<< "\t\t\tThank you for your business!"
		<< endl << endl << endl << endl << endl << endl;
	this->PressAnyKeyToContinue();
}

// Displays a compile-time-defined message to the user
void UI::ShowErrorMessage(char *message)
{
	this->ClearScreen();
	cout << endl << endl
		<< " *****  " << message << "  *****" << endl
		<< endl << endl << endl << endl << endl << endl;
	this->PressAnyKeyToContinue();
}

// Function to display transaction history
void UI::ShowTransactionHistory(vector<Page> transactionHistory, string firstName, string lastName)
{
	unsigned int currentPage = 0;
	int keyboardHit = 0;

	while (keyboardHit != KEY_ESC)
	{
		this->ClearScreen();

		cout << endl << " Transaction History for " + firstName + " " + lastName << endl << endl << endl;
		cout << "\t     Number  |    Amount    | Type |         Date" << endl;
		cout << "\t    -----------------------------------------------------" << endl;

		if (transactionHistory.size() > 0)
		{
			for (unsigned int i = 0; i < transactionHistory[currentPage].GetNumberOfLines(); i++)
			{
				cout << transactionHistory[currentPage].GetLine(i) << endl;
			}

			if (transactionHistory[currentPage].GetNumberOfLines() < transactionHistory[currentPage].GetMaximumNumberOfLines())
			{
				unsigned int numberOfBlankLines = transactionHistory[currentPage].GetMaximumNumberOfLines() - transactionHistory[currentPage].GetNumberOfLines();

				for (unsigned int i = 0; i < numberOfBlankLines; i++)
				{
					cout << endl;
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < 10; i++)
			{
				cout << endl;
			}
		}		

		cout << endl << endl << endl << endl;

		cout << " <--- Previous Page (Left Arrow)\t\t   Next Page (Right Arrow) --->" << endl << endl << endl;
		cout << " Press Escape key to return to Main Menu";

		keyboardHit = _getch();
		switch (keyboardHit)
		{
		case KEY_LEFT:
			if (currentPage > 0)
			{
				currentPage--;
			}
			break;
		case KEY_RIGHT:
			if (currentPage < (transactionHistory.size() - 1))
			{
				currentPage++;
			}
		}
	}
	
}

// Another history function, this time for transfers - they look slightly different
void UI::ShowTransferHistory(vector<Page> transferHistory, string firstName, string lastName)
{
	unsigned int currentPage = 0;
	int keyboardHit = 0;

	while (keyboardHit != KEY_ESC)
	{
		this->ClearScreen();

		cout << endl << " Transfer History for " + firstName + " " + lastName << endl << endl << endl;
		cout << "     Transfer | Source |  Dest. |   Transfer   |" << endl;
		cout << "      Number  |  Acct  |  Acct  |    Amount    |         Date" << endl;
		cout << "    ------------------------------------------------------------------" << endl;

		if (transferHistory.size() > 0)
		{
			for (unsigned int i = 0; i < transferHistory[currentPage].GetNumberOfLines(); i++)
			{
				cout << transferHistory[currentPage].GetLine(i) << endl;
			}

			if (transferHistory[currentPage].GetNumberOfLines() < transferHistory[currentPage].GetMaximumNumberOfLines())
			{
				unsigned int numberOfBlankLines = transferHistory[currentPage].GetMaximumNumberOfLines() - transferHistory[currentPage].GetNumberOfLines();

				for (unsigned int i = 0; i < numberOfBlankLines; i++)
				{
					cout << endl;
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < 10; i++)
			{
				cout << endl;
			}
		}

		cout << endl << endl << endl << endl;

		cout << " <--- Previous Page (Left Arrow)\t\t   Next Page (Right Arrow) --->" << endl << endl << endl;
		cout << " Press Escape key to return to Main Menu";

		keyboardHit = _getch();
		switch (keyboardHit)
		{
		case KEY_LEFT:
			if (currentPage > 0)
			{
				currentPage--;
			}
			break;
		case KEY_RIGHT:
			if (currentPage < (transferHistory.size() - 1))
			{
				currentPage++;
			}
		}
	}
}

bool UI::ShowChangeAccountStatusPrompt()
{
	this->ClearScreen();
	cout << endl << endl << endl << "  Make Account Inactive? (Y/N)";

	int key = _getch();

	if (key == 121)
	{
		cout << endl << endl << endl << endl << endl << endl << endl << endl
			<< "  Are you absolutely sure you want to make this account INACTIVE?" 
			<< endl << endl << endl << endl
			<< "  You will be logged out immediately following this action. (Y/N)";
		key = _getch();
		if (key == 121)
		{
			return true;
		}
		else
			return false;
	}		
	else
		return false;	
}

// Clear the screen - THIS CODE IS NOT MY OWN.
// I created the ClearScreen function using 
// code from http://www.cplusplus.com/articles/4z18T05o/
void UI::ClearScreen()
{
	HANDLE hStdout;
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Get the number of character cells in the current buffer. 

	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if (!FillConsoleOutputCharacter(hStdout, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// Get the current text attribute.

	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
		return;

	// Set the buffer's attributes accordingly.

	if (!FillConsoleOutputAttribute(hStdout, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// Put the cursor at its home coordinates.

	SetConsoleCursorPosition(hStdout, coordScreen);
}

// Pause the screen
void UI::PauseScreen()
{
	while (!_kbhit()){}
}

// Pause the screen, Display "Press any key..." and wait for 
// the user to strike a key.
void UI::PressAnyKeyToContinue()
{
	cout << "  Press any key to continue...";
	while (!_kbhit()){}
	char key = _getch();
}

/**************** CODE TO CLEAR THE INPUT BUFFER ****************
****************************************************************/
void UI::ClearBuffer()
{
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}