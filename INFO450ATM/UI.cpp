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

// Display standard login to the user
void UI::ShowLoginPrompt()
{
	this->ClearScreen();
	cout << endl
		<< "\t\t\t***********************" << endl
		<< "\t\t\t* Welcome to DAT Bank *" << endl
		<< "\t\t\t***********************" << endl
		<< endl
		<< endl
		<< "Please enter your email: ";
}

// Prompt the user to enter a PIN
void UI::ShowPINPrompt()
{
	cout << endl << endl
		<< "Please enter PIN: ";
}

// Display the menu of possible transactions to the user as selections 1-6
void UI::ShowTransactionTypeMenu(string custFirstName, string custLastName)
{
	char select1 = '*';
	char select2 = ' ';
	char select3 = ' ';
	char select4 = ' ';
	char select5 = ' ';
	char select6 = ' ';

	this->ClearScreen();
	cout << endl
		<< "\t\t\t    Welcome " + custFirstName + " " + custLastName
		<< endl << endl
		<< "Please make a selection (1-6):" << endl
		<< endl
		<< "\t[" << select1 << "]1) Make a withdrawal" << endl      //<---- Choice #1
		<< "\t[" << select2 << "]2) Make a deposit" << endl         //<---- Choice #2
		<< "\t[" << select3 << "]3) Check account balance" << endl  //<---- Choice #3
		<< "\t[" << select4 << "]4) Make a transfer" << endl		 //<---- Choice #4
		<< "\t[" << select5 << "]5) See Account History" << endl	 //<---- Choice #5
		<< "\t[" << select6 << "]6) Logout" << endl                 //<---- Choice #6
		<< endl;

	switch (getch())
	{
		case VK_DOWN: if (select1 == '*')
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
		case VK_UP: if (select1 == '*')
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
		case VK_RETURN: if (select1 == '*')
						{
							
						}
	}
	this->PauseScreen();
}

// Display the menu of possible transactions amounts to the user.
void UI::ShowTransactionAmountMenu(char *actionToBePerformed)
{
	this->ClearScreen();
	cout << endl
		<< "\t\t   Please select amount to be " << actionToBePerformed << ":"
		<< endl << endl
		<< "Please type amount below:" << endl
		<< "  $20.00" << endl
		<< "  $40.00" << endl
		<< "  $60.00" << endl
		<< "  $80.00" << endl
		<< "  $100.00" << endl
		<< endl
		<< "Enter Amount (increments of $20): $";
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

void UI::NaviMenu()
{
	// maybe array later
	//char select[6];
	char select1 = '*';
	char select2 = ' ';
	char select3 = ' ';
	char select4 = ' ';
	char select5 = ' ';
	char select6 = ' ';

	switch (getch())
	{
		case VK_DOWN: if (select1 == '*')
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
		case VK_UP: if (select1 == '*')
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
	}
}