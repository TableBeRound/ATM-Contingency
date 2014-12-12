#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include "Page.h"

using namespace std;

// These are preprocessor directives used in 
// the logic which facilitates menu navigation. 
// Inspiration for this code and the code in the 
// switches which use these directives was found at:
// http://www.stackoverflow.com/questions/24708700/c-detect-when-user-presses-arrow-key
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27

// The Display object represents the "screen" of the UI
class UI
{

public:
	// Constructor & destructor
	UI();
	~UI();

	// All of these functions print things to the screen.
	// The function names are pretty self-explanatory.
	string ShowLoginPrompt();
	int ShowPINPrompt();
	int ShowTransactionTypeMenu(string custFirstName, string custLastname);
	double ShowTransactionAmountMenu(char *actionToBePerformed);
	int ShowDestinationAccountPrompt();
	void ShowAccountBalance(string custName, int acctNum, double acctBalance);
	void ShowTransactionSuccessMessage();
	void ShowErrorMessage(char *message);
	void ShowTransactionHistory(vector<Page> transactionHistory, string firstName, string lastName);

	// These functions are frequently used
	// to manipulate output to the screen.
	void ClearScreen();
	void PauseScreen();
	void PressAnyKeyToContinue(); //<--- Pauses screen and waits for a key press
	void ClearBuffer();           //<--- used to clear cin buffer if needed
};

#endif