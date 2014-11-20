// Danny Glidewell, Tucker Lavell, Anthony Tran
// TR 5:30-6:45
// Assignment: ATM Redo
// This program will simulate a text based version of an ATM interface and interaction
// for the Shallow prototype of the ATM, there are only successful interactions with this ATM

#include <iostream>
#include <cmath>
#include "Windows.h"
#include "Conio.h"
#include "UI.h"
#include "ATM.h"

using namespace std;

// Class prototypes
UI *ui = new UI();
ATM *atm = new ATM();

int main() {
	atm->login();
	return 0;
}
