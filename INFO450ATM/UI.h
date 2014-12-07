#ifndef UI_H
#define UI_H

#include <string>

using namespace std;

// The Display object represents the "screen" of the UI
class UI
{
public:
	// Constructor & destructor
	UI();
	~UI();

	// All of these functions print things to the screen.
	// The function names are pretty self-explanatory.
	void ShowLoginPrompt();
	void ShowPINPrompt();
	void ShowTransactionTypeMenu(string custFirstName, string custLastname);
	void ShowTransactionAmountMenu(char *actionToBePerformed);
	void ShowAccountBalance(string acctNum, double acctBalance);
	void ShowTransactionSuccessMessage();
	void ShowErrorMessage(char *message);

	// These functions are frequently used
	// to manipulate output to the screen.
	void ClearScreen();
	void PauseScreen();
	void PressAnyKeyToContinue(); //<---- Pauses screen and waits for a key press
	void ClearBuffer(); //<--- used to clear cin buffer if needed
	void NaviMenu(); //<---navigate menus using arrow keys
};

#endif