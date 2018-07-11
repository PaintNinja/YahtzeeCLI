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

// http://www.cplusplus.com/reference/array/array/
// https://www.programiz.com/cpp-programming/library-function/cstdlib/srand
// http://www.bogotobogo.com/cplusplus/RandomNumbers.php
vector<int> rollDice(int amountOfDies, bool debugMode) {
	srand(time(0));  // seed the pseudo random number generator used by the rand() function with the current time.
					 // If this is omitted, the rand() function would always be seeded with the default value of 1, which can make for a predictable game

	vector<int> diceResultsArray; // https://stackoverflow.com/questions/755835/how-to-add-element-to-c-array
								  // a vector can store a variable length array of integers.

	diceResultsArray.clear(); // http://www.cplusplus.com/reference/vector/vector/clear/
							  // make sure the array is empty before adding rolled dies to it

	for (int i = 0; i < amountOfDies; i++) {
		diceResultsArray.push_back((rand() % 6) + 1);

		if (debugMode) {
			debugMsg(0, "", false);
			cout << diceResultsArray.at(i) << endl; // show the value of each dice roll result if debugMode is enabled
		}

	}
	return diceResultsArray;
}

void singlePlayerGame(bool debugMode) {
	int onesCombination = 0;
	int twosCombination = 0;
	int threesCombination = 0;
	int foursCombination = 0;
	int fivesCombination = 0;
	int sixesCombination = 0;
	int sumCombination = 0;
	int bonusCombination = 0;
	int threeOfAKindCombination = 0;
	int fourOfAKindCombination = 0;
	int fullHouseCombination = 0;
	int smallStraightCombination = 0;
	int largeStraightCombination = 0;
	int chanceCombination = 0;
	int yahtzeeCombination = 0;
	int totalScore = 0;

	vector<int> yourDies;
	vector<int> yourRoll;

	string keepDies;
	int rollCount = 0;

	cout << endl << "Yahtzee singleplayer" << endl;
	cout << "====================" << endl;
	cout << "Welcome to Yahtzee! For instructions, please consult the user manual." << endl;
	
	cout << endl << "Your score card" << endl;
	cout << "---------------" << endl;
	cout << "Ones: " << onesCombination << endl;
	cout << "Twos: " << twosCombination << endl;
	cout << "Threes: " << threesCombination << endl;
	cout << "Fours: " << foursCombination << endl;
	cout << "Fives: " << fivesCombination << endl;
	cout << "Sixes: " << sixesCombination << endl;
	cout << "Sum: " << sumCombination << endl;
	cout << "Bonus: " << bonusCombination << endl;
	cout << "Three of a kind: " << threeOfAKindCombination << endl;
	cout << "Four of a kind: " << fourOfAKindCombination << endl;
	cout << "Full house: " << fullHouseCombination << endl;
	cout << "Small straight: " << smallStraightCombination << endl;
	cout << "Large straight: " << largeStraightCombination << endl;
	cout << "Chance: " << chanceCombination << endl;
	cout << "Yahtzee: " << yahtzeeCombination << endl;
	cout << "Total score: " << totalScore << endl;

	cout << endl << "Your dies" << endl;
	cout << "---------" << endl;
	for (int i = 0; i < yourDies.size(); i++) {
		if (i == (yourDies.size() - 1)) {
			cout << yourDies.at(i) << endl; // if this is the last element in the yourDies vector, don't add a space and instead finish off with a line ending.
		} else {
			cout << yourDies.at(i) << " "; // if not the last element in the yourDies vector, add a space for the next element.
		}
	}

	rollCount++;
	if (rollCount < 4 | yourDies.size() < 5) { // don't allow rolling again if the max amount of rolls is reached or the amount of dies in your dies is 5.
		cout << endl << "Your roll (" << rollCount << "/3)" << endl;
		cout << "---------------" << endl;
		yourRoll = rollDice((5 - yourDies.size()), debugMode); // you must have 5 dies in "your dies" before you can make a move.
															  // roll the amount of dies needed to reach 5 dies total in "your dies", taking into account the amount of dies already in "your dies"
		cout << "You rolled: ";
		for (int i = 0; i < yourRoll.size(); i++) { // list each rolled dice
			if (i == (yourRoll.size() - 1)) {
				cout << yourRoll.at(i) << endl;
			} else {
				cout << yourRoll.at(i) << " ";
			}
		}
	}

	if (yourDies.size() < 5 | (yourDies.size() < 5 && rollCount > 3)) { // ask the user what dies to keep if they haven't chosen 5 for yourDies yet.
																	   // if they haven't chosen 5 dies yet and they've done their 3 rolls, keep on asking them to pick dies from the last roll until they have 5
		cout << endl << "Enter the dies you want to keep (if any): "; // ask the player if they want to keep any of their rolled dies
		keepDies = "";
		cin >> keepDies; // grab input from the user and store it in the string "keepDies"
		cout << endl;
	}

	pause();
}

int main() {
	bool debugMode = false; // initialise the debugMode variable with a default value of false

	// Textart from http://www.patorjk.com/software/taag/#p=display&f=Standard&t=Yahtzee . backslash characters were escaped.
	cout << " __   __    _     _                " << endl;
	cout << " \\ \\ / /_ _| |__ | |_ _______  ___ " << endl;
	cout << "  \\ V / _` | '_ \\| __|_  / _ \\/ _ \\" << endl;
	cout << "   | | (_| | | | | |_ / /  __/  __/" << endl;
	cout << "   |_|\\__,_|_| |_|\\__/___\\___|\\___|" << endl;

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
		singlePlayerGame(debugMode);
	} else if (menuResult == 2 | menuResult == 3) {
		cout << "Error: Unimplemented." << endl;
		goto showMainMenu;
	} else if (menuResult == 4) {
		goto showMainMenu;
	} else if (menuResult == 9) {
		return 0; // quit the game with a return code of 0 (application closing with no errors)
	}
	pause();
}