 // YahtzeeCLI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

 // https://stackoverflow.com/questions/21257544/c-wait-for-user-input
// http://www.cplusplus.com/doc/tutorial/functions/
void pause() {
	cout << "Press any key to continue . . . " << endl;
	_getch(); // needs conio.h, this function waits for a character input from terminal and then returns its value
	return;
}

void debugMsg(int typeID, string msg, bool shouldEndl) { // this function gets a typeID and msg and prints an appropriate debug-formatted message to the console.
	string type = "DEBUG: "; // fallback to "DEBUG: " as the type if an invalid typeID was specified 
	if (typeID == 0) {
		type = "INFO: ";
	} else if (typeID == 1) {
		type = "WARNING: ";
	} else if (typeID == 2) {
		type = "ERROR: ";
	}

	if (shouldEndl) {
		cout << type << msg << endl;
	} else {
		cout << type << msg;
	}
}

int mainMenu() {
	string result;
	RepromptMainMenu:
	result = "";
	cout << endl;
	cout << "Main menu" << endl;
	cout << "=========" << endl;
	cout << "1) Play singleplayer" << endl;
	cout << "2) Play multiplayer" << endl;
	cout << "3) Options" << endl;
	cout << "4) Enable debug mode" << endl;
	cout << "Q) Quit" << endl;
	cout << "Please enter a number/letter: ";
	cin >> result;
	cout << endl;
	if (result == "1") {
		return 1;
	} else if (result == "2") {
		return 2;
	} else if (result == "3") {
		return 3;
	} else if (result == "4") {
		return 4;
	} else if (result == "q" || result == "Q") {
		return 9;
	} else {
		cout << "Sorry, please enter a number between 1 and 4 inclusive, or enter Q to quit." << endl;
		goto RepromptMainMenu;
	}
	return 0;
}

int menu(int menuID) { // a junction function that grabs a menuID and translates it into a menu function call, returning 99 if the menuID is not found
	if (menuID == 0) {
		return mainMenu();
	}
	return 99; // return 99 if the menuID requested is unknown
}

void game() {

}

  // http://www.cplusplus.com/reference/array/array/
 // https://www.programiz.com/cpp-programming/library-function/cstdlib/srand
// http://www.bogotobogo.com/cplusplus/RandomNumbers.php
vector<int> rollDice(int amountOfDies, bool debugMode) {
	srand(time(0));  // seed the pseudo random number generator used by the rand() function with the current time.
					// If this is omitted, the rand() function would always be seeded with the default value of 1, which can make for a predictable game

	vector<int> diceResultsArray; // https://stackoverflow.com/questions/755835/how-to-add-element-to-c-array
								 // a vector can store a variable length array of integers.
	
	for (int i = 0; i < amountOfDies; i++) {
		diceResultsArray.push_back((rand() % 6) + 1);

		if (debugMode) {
			debugMsg(0, "", false);
			cout << diceResultsArray.at(i) << endl; // show the value of each dice roll result if debugMode is enabled
		}
		
	}
	return diceResultsArray;
}

int main() {
	bool debugMode = false; // initialise the debugMode variable with a default value of false
	cout << "Hello world!" << endl;

	// testing random number generation in a range
	int i = 0;
	while (i++ < 20) {
		int num = (rand() % 6) + 1;
		cout << num << " ";
	}
	cout << endl;
	pause();

	showMainMenu:
	int menuResult = menu(0); // open a menu with menuID 0 (the main menu) and store the retrieved result to a new integer variable called "menuResult"
	if (menuResult == 4) {
		debugMode = true;
		debugMsg(0, "Debug mode has been enabled", true);
	}

	if (debugMode == true) {
		debugMsg(0, "menuResult: ", false);
		cout << menuResult << endl; // if debug mode is on, show the retrieved result from earlier
	}

	if (menuResult == 1) {
		rollDice(5, debugMode);
		pause();
	} else if (menuResult == 2 | menuResult == 3) {
		cout << "Error: Unimplemented." << endl;
		goto showMainMenu;
	} else if (menuResult == 4) {
		goto showMainMenu;
	} else if (menuResult == 9) {
		return 0; // quit the game with a return code of 0 (no errors)
	}
	pause();
}