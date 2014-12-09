#include "UI.h"
#include <iostream>
#include <iomanip>
#include "Windows.h"
#include "Conio.h"
#include "ATM.h" // <----------------------------THIS NEEDS TO DISAPPEAR!!!

using namespace std;

ATM *atm = new ATM(); // <----------------------------THIS NEEDS TO DISAPPEAR!!!
// Default constructor
UI::UI()
{
}

// Default destructor
UI::~UI()
{
}

// Display standard login to the user
string UI::ShowLoginPrompt()
{
	string emailInput = "";

	this->ClearScreen();
	cout << endl
		<< "\t\t\t***********************" << endl
		<< "\t\t\t* Welcome to DAT Bank *" << endl
		<< "\t\t\t***********************" << endl
		<< endl
		<< endl
		<< "Please enter your email: ";
	cin >> emailInput;

	return emailInput;
}

// Prompt the user to enter a PIN
int UI::ShowPINPrompt()
{
	int pinInput = NULL;

	cout << endl << endl
		<< "Please enter PIN: ";
	cin >> pinInput;

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
	int keyboardHit = 0;
	int userSelection = 0;

	// As long as the user hasn't hit the Enter key loop
	while (keyboardHit != KEY_ENTER)
	{
		this->ClearScreen();
		cout << endl
			<< "\t\t\t    Welcome " + custFirstName + " " + custLastName
			<< endl << endl
			<< "Please use the UP/DOWN arrow keys to make a selection (1-6):" << endl
			<< endl
			<< "\t[" << select1 << "]1) Make a withdrawal" << endl      //<---- Choice #1
			<< "\t[" << select2 << "]2) Make a deposit" << endl         //<---- Choice #2
			<< "\t[" << select3 << "]3) Check account balance" << endl  //<---- Choice #3
			<< "\t[" << select4 << "]4) Make a transfer" << endl		 //<---- Choice #4
			<< "\t[" << select5 << "]5) See Account History" << endl	 //<---- Choice #5
			<< "\t[" << select6 << "]6) Logout" << endl                 //<---- Choice #6
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
				select1 = '*';
			}
			break;

		case KEY_UP:
			if (select1 == '*')
			{
				select1 = ' ';
				select6 = '*';
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
	double transactionAmount = NULL;
	int keyboardHit = NULL;

	while (keyboardHit != KEY_ENTER)
	{
		this->ClearScreen();
		cout << endl
			<< "\t\t   Please select amount to be " << actionToBePerformed << ":"
			<< endl << endl
			<< "Please use the UP/DOWN arrow keys to make a selection (1-6):" << endl
			<< endl
			<< "\t[" << amount1 << "]1) $20" << endl      //<---- Choice #1
			<< "\t[" << amount2 << "]2) $40" << endl      //<---- Choice #2
			<< "\t[" << amount3 << "]3) $60" << endl      //<---- Choice #3
			<< "\t[" << amount4 << "]4) $80" << endl      //<---- Choice #4
			<< "\t[" << amount5 << "]5) $100" << endl	  //<---- Choice #5			
			<< endl;

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

	return transactionAmount;
}

// Display the menu of possible transactions amounts to the user.
void UI::ShowAccountBalance(string acctNum, double acctBalance)
{
	this->ClearScreen();
	cout << endl
		<< " *******************" << endl
		<< " * Current Balance *" << endl
		<< " *******************" << endl
		<< endl << endl
		<< "The account for " + acctNum + " has: $" << std::fixed << std::setprecision(2) << acctBalance
		<< endl << endl << endl << endl << endl << endl;
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
	cout << "Press any key to continue...";
	while (!_kbhit()){}
	char key = _getch();
}

/**************** CODE TO CLEAR THE INPUT BUFFER ****************
****************************************************************/
// may not be used
void UI::ClearBuffer()
{
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}