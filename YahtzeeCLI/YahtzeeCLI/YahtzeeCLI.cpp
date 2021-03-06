 // YahtzeeCLI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <ctime>
#include <vector>
#include <regex>
#include <istream>
#include <sstream>

using namespace std;

 // https://stackoverflow.com/questions/21257544/c-wait-for-user-input
// http://www.cplusplus.com/doc/tutorial/functions/
void pause() {
	cout << "Press any key to continue . . . " << endl;
	_getch(); // needs conio.h, this function waits for a character input from terminal and then returns its value
	return;
}

 // https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
// String splitting function by Jonathan Boccara
std::vector<std::string> split(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
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
void debugMsg(int typeID, string preMsg, int msgInt, string postMsg, bool shouldEndl) {
	string type = "DEBUG: ";
	if (typeID == 0) {
		type = "INFO: ";
	} else if (typeID == 1) {
		type = "WARNING: ";
	} else if (typeID == 2) {
		type = "ERROR: ";
	}

	if (shouldEndl) {
		cout << type << preMsg << msgInt << postMsg << endl;
	} else {
		cout << type << preMsg << msgInt << postMsg;
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
			debugMsg(0, "", diceResultsArray.at(i), "", true); // show the value of each dice roll result if debugMode is enabled
		}

	}
	return diceResultsArray;
}

string startPlayer1Round(bool debugMode, int onesCombination, int twosCombination, int threesCombination, int foursCombination, int fivesCombination, int sixesCombination,
					     int sumCombination, int bonusCombination, int threeOfAKindCombination, int fourOfAKindCombination, int fullHouseCombination, int smallStraightCombination,
					     int largeStraightCombination, int chanceCombination, int yahtzeeCombination, int totalScore, int rollCount) {

	vector<int> yourDies;
	vector<int> yourRoll;

	string keepDies;
	vector<string> keepDiesVector;
	
	continuePlayer1Round:
	cout << endl << "Your score card" << endl;
	cout << "---------------" << endl;
	if (onesCombination == -1) { // if a combination has been picked when its score was zero, show the score as zero but keep it internally as -1 to keep track of it being picked already
		cout << "Ones: 0" << endl;
	} else {
		cout << "Ones: " << onesCombination << endl;
	}

	if (twosCombination == -1) {
		cout << "Twos: 0" << endl;
	} else {
		cout << "Twos: " << twosCombination << endl;
	}

	if (threesCombination == -1) {
		cout << "Threes: 0" << endl;
	} else {
		cout << "Threes: " << threesCombination << endl;
	}

	if (foursCombination == -1) {
		cout << "Fours: 0" << endl;
	} else {
		cout << "Fours: " << foursCombination << endl;
	}

	if (fivesCombination == -1) {
		cout << "Fives: 0" << endl;
	} else {
		cout << "Fives: " << fivesCombination << endl;
	}

	if (sixesCombination == -1) {
		cout << "Sixes: 0" << endl;
	} else {
		cout << "Sixes: " << sixesCombination << endl;
	}

	cout << "Sum: " << sumCombination << endl;
	cout << "Bonus: " << bonusCombination << endl;

	if (threeOfAKindCombination == -1) {
		cout << "Three of a kind: 0" << endl;
	} else {
		cout << "Three of a kind: " << threeOfAKindCombination << endl;
	}

	if (fourOfAKindCombination == -1) {
		cout << "Four of a kind: 0" << endl;
	} else {
		cout << "Four of a kind: " << fourOfAKindCombination << endl;
	}

	if (fullHouseCombination == -1) {
		cout << "Full house: 0" << endl;
	} else {
		cout << "Full house: " << fullHouseCombination << endl;
	}

	if (smallStraightCombination == -1) {
		cout << "Small straight: 0" << endl;
	} else {
		cout << "Small straight: " << smallStraightCombination << endl;
	}

	if (largeStraightCombination == -1) {
		cout << "Large straight: 0" << endl;
	} else {
		cout << "Large straight: " << largeStraightCombination << endl;
	}

	if (chanceCombination == -1) {
		cout << "Chance: 0" << endl;
	} else {
		cout << "Chance: " << chanceCombination << endl;
	}

	if (yahtzeeCombination == -1) {
		cout << "Yahtzee: 0" << endl;
	} else {
		cout << "Yahtzee: " << yahtzeeCombination << endl;
	}
	cout << "Total score: " << totalScore << endl;

	cout << endl << "Your dies" << endl;
	cout << "---------" << endl;
	for (int i = 0; i < yourDies.size(); i++) { // for each die in the yourDies vector
		if (i == (yourDies.size() - 1)) {
			cout << yourDies.at(i) << endl; // if this is the last element in the yourDies vector, don't add a space and instead finish off with a line ending.
		} else {
			cout << yourDies.at(i) << " "; // if not the last element in the yourDies vector, add a space for the next element.
		}
	}

	rollCount++;
	if (debugMode) {
		debugMsg(0, "rollCount: ", rollCount, "", true); // show the rollCount before the following if statement if in debugMode 
	}
	if (rollCount < 4 & yourDies.size() < 5) { // don't allow rolling again if the max amount of rolls is reached or the amount of dies in your dies is 5.
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
	} else if (rollCount > 3) {
		cout << endl << "Your previous roll" << endl;
		cout << "------------------" << endl;
		cout << "You rolled: ";
		for (int i = 0; i < yourRoll.size(); i++) { // list each rolled dice
			if (i == (yourRoll.size() - 1)) {
				cout << yourRoll.at(i) << endl;
			} else {
				cout << yourRoll.at(i) << " ";
			}
		}
	}

	if (yourDies.size() < 5) { // ask the user what dies to keep if they haven't chosen 5 for yourDies yet.

								// if they haven't chosen 5 dies yet and they've done their 3 rolls, keep on asking them to pick dies from the last roll until they have 5
		repromptKeepDies:
		if (yourDies.size() < 5 && rollCount > 3) {
			cout << endl << "Enter all the remaining dies to continue: "; // TODO: Automate this
		} else {
			cout << endl << "Enter the dies you want to keep (if any, enter 0 for none): "; // ask the player if they want to keep any of their rolled dies
		}
		keepDies = "";
		cin >> keepDies; // grab input from the user and store it in the string "keepDies"
		cout << endl;

		// format the inputted string before splitting it, by replacing any fullstops with commas (they are very close to eachother on the keyboard, so using a fullstop is likely to be an accident).
		// https://stackoverflow.com/questions/5343190/how-do-i-replace-all-instances-of-a-string-with-another-string
		/*keepDies = regex_replace(keepDies, std::regex("/\./g"), ",");
		if (debugMode) {
		debugMsg(0, "keepDies after formatting: ", false);
		cout << keepDies << endl;
		}*/
		// ^ commented out as not working yet ^

		//char keepDiesChar[] = keepDies.c_str();
		// https://en.cppreference.com/w/cpp/string/byte/strtok
		//char *keepDiesToken = strtok(keepDiesChars, ",");

		if (keepDies == "0") {
			// go onto the next roll if the player doesn't pick any dies
			goto continuePlayer1Round;
		} else {
			// https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
			keepDiesVector = split(keepDies, ',');

			if (debugMode) { // show what each split result is before preceeding if debugMode is enabled
				for (int i = 0; i < keepDiesVector.size(); i++) {
					debugMsg(0, "keepDiesVector.at(", i, ") = ", false);
					cout << keepDiesVector.at(i) << endl;

					debugMsg(0, "yourRoll.at(", i, ") = ", false);
					cout << yourRoll.at(i) << endl;
				}
				pause();
			}

			// Validate input
			for (int i = 0; i < keepDiesVector.size(); i++) {
				if ((find(yourRoll.begin(), yourRoll.end(), stoi(keepDiesVector.at(i))) != yourRoll.end())) { // check that the user inputted numbers match the options available in yourRoll.
					// all good
				} else {
					cout << "Sorry, you can only enter dies to keep that you have rolled." << endl;
					goto repromptKeepDies;
				}
			}

			for (int i = 0; i < keepDiesVector.size(); i++) {
				yourDies.push_back(stoi(keepDiesVector.at(i))); // convert the keepDiesVector entry from a string to an int using the stoi function, and put it in the yourDies vector
			}
		}
	} else {
		rollCount = 0; // reset the rollCount back to 0 once the required amount of dies have been chosen

		 // calculate the scores for combinations, then ask what combination the player wants to use
		// https://stackoverflow.com/questions/24139428/check-if-element-is-in-the-list-contains
		int preOnes = 0;
		if ((find(keepDiesVector.begin(), keepDiesVector.end(), "1") != keepDiesVector.end())) { // if the keepDiesVector contains the number 1, pre-calculate the score for 1s (amount of 1s multiplied by 1)

			for (int i = 0; i < keepDiesVector.size(); i++) { // for each entry in the keepDiesVector
				if (keepDiesVector.at(i) == "1") { // if the entry is a one,
					preOnes++; // add it to the preOnes count and move onto the next entry
				}
			}
		}

		int preTwos = 0;
		if ((find(keepDiesVector.begin(), keepDiesVector.end(), "2") != keepDiesVector.end())) { // if the keepDiesVector contains the number 2, pre-calculate the score for 2s (amount of 2s multiplied by 2)

			int preTwosCount = 0;
			for (int i = 0; i < keepDiesVector.size(); i++) { // for each entry in the keepDiesVector
				if (keepDiesVector.at(i) == "2") { // if the entry is a two,
					preTwosCount++; // add it to preTwosCount
					preTwos = 0; // reset preTwos back to zero
					preTwos = 2 * preTwosCount; // calculate the score for choosing the "Twos" combination based on the amount of twos found so far in "Your dies" (keepDiesVector)
				}
			}
		}

		int preThrees = 0;
		if ((find(keepDiesVector.begin(), keepDiesVector.end(), "3") != keepDiesVector.end())) { // do the same for 3s, 4s, 5s, and 6s.
			int preThreesCount = 0;
			for (int i = 0; i < keepDiesVector.size(); i++) {
				if (keepDiesVector.at(i) == "3") {
					preThreesCount++;
					preThrees = 0;
					preThrees = 3 * preThreesCount;
				}
			}
		}

		int preFours = 0;
		if ((find(keepDiesVector.begin(), keepDiesVector.end(), "4") != keepDiesVector.end())) {
			int preFoursCount = 0;
			for (int i = 0; i < keepDiesVector.size(); i++) {
				if (keepDiesVector.at(i) == "4") {
					preFoursCount++;
					preFours = 0;
					preFours = 4 * preFoursCount;
				}
			}
		}

		int preFives = 0;
		if ((find(keepDiesVector.begin(), keepDiesVector.end(), "5") != keepDiesVector.end())) {
			int preFivesCount = 0;
			for (int i = 0; i < keepDiesVector.size(); i++) {
				if (keepDiesVector.at(i) == "5") {
					preFivesCount++;
					preFives = 0;
					preFives = 5 * preFivesCount;
				}
			}
		}

		int preSixes = 0;
		if ((find(keepDiesVector.begin(), keepDiesVector.end(), "6") != keepDiesVector.end())) {
			int preSixesCount = 0;
			for (int i = 0; i < keepDiesVector.size(); i++) {
				if (keepDiesVector.at(i) == "6") {
					preSixesCount++;
					preSixes = 0;
					preSixes = 6 * preSixesCount;
				}
			}
		}

		int preThreeOfAKind = 0;
		int preFourOfAKind = 0;
		int preFullHouse = 0;
		int preXOfAKindOnesCount = 0;
		int preXOfAKindTwosCount = 0;
		int preXOfAKindThreesCount = 0;
		int preXOfAKindFoursCount = 0;
		int preXOfAKindFivesCount = 0;
		int preXOfAKindSixesCount = 0;
		int preDiesSum = 0;
		for (int i = 0; i < keepDiesVector.size(); i++) { // for each dice in the keepDiesVector, count how many of each number there are, and calculate the sum of all the dies
			if (keepDiesVector.at(i) == "1") { // single character string comparison seems faster than stoi conversion + int comparison
				preXOfAKindOnesCount++;
			} else if (keepDiesVector.at(i) == "2") {
				preXOfAKindTwosCount++;
			} else if (keepDiesVector.at(i) == "3") {
				preXOfAKindThreesCount++;
			} else if (keepDiesVector.at(i) == "4") {
				preXOfAKindFoursCount++;
			} else if (keepDiesVector.at(i) == "5") {
				preXOfAKindFivesCount++;
			} else if (keepDiesVector.at(i) == "6") {
				preXOfAKindSixesCount++;
			}
			preDiesSum += stoi(keepDiesVector.at(i));
		}
		if (preXOfAKindOnesCount == 3 | preXOfAKindTwosCount == 3 | preXOfAKindThreesCount == 3 | preXOfAKindFoursCount == 3 | preXOfAKindFivesCount == 3 | preXOfAKindSixesCount == 3) {
			preThreeOfAKind = preDiesSum; // if there are three of the same dies, set the pre-calculated score for threeOfAKind to the sum of all the dies
		}

		if (preXOfAKindOnesCount == 4 | preXOfAKindTwosCount == 4 | preXOfAKindThreesCount == 4 | preXOfAKindFoursCount == 4 | preXOfAKindFivesCount == 4 | preXOfAKindSixesCount == 4) {
			preFourOfAKind = preDiesSum; // do the same for four of a kind
		}

		// Yahtzee
		int preYahtzee = 0;
		if (preXOfAKindOnesCount == 5 | preXOfAKindTwosCount == 5 | preXOfAKindThreesCount == 5 | preXOfAKindFoursCount == 5 | preXOfAKindFivesCount == 5 | preXOfAKindSixesCount == 5) {
			preYahtzee = 50; // if the player can get a five of a kind (a yahtzee), set the pre-calculated score to 50.
		}

		// Small straight
		int preSmallStraight = 0;
		if (preXOfAKindOnesCount == 1 & preXOfAKindTwosCount == 1 & preXOfAKindThreesCount == 1 & preXOfAKindFoursCount == 1) {
			preSmallStraight = 30; // if the player can get numbers 1,2,3,4 or 2,3,4,5 or 3,4,5,6, then set the pre-calculated score for smallStraight to 30.
		} else if (preXOfAKindTwosCount == 1 & preXOfAKindThreesCount == 1 & preXOfAKindFoursCount == 1 & preXOfAKindFivesCount == 1) {
			preSmallStraight = 30;
		} else if (preXOfAKindThreesCount == 1 & preXOfAKindFoursCount == 1 & preXOfAKindFivesCount == 1 & preXOfAKindSixesCount == 1) {
			preSmallStraight = 30;
		}

		// Large straight
		int preLargeStraight = 0;
		if (preXOfAKindOnesCount == 1 & preXOfAKindTwosCount == 1 & preXOfAKindThreesCount == 1 & preXOfAKindFoursCount == 1 & preXOfAKindFivesCount == 1) {
			preLargeStraight = 40; // if the player can get numbers 1,2,3,4,5 or 2,3,4,5,6, then set the pre-calculated score for largeStraight to 40.
		} else if (preXOfAKindTwosCount == 1 & preXOfAKindThreesCount == 1 & preXOfAKindFoursCount == 1 & preXOfAKindFivesCount == 1 & preXOfAKindSixesCount == 1) {
			preLargeStraight = 40;
		}

		// A full house needs a pair and a three of a kind. A five of a kind doesn't count (that's a Yahtzee, not a full house).
		if (preXOfAKindOnesCount == 2) {
			if (preXOfAKindTwosCount == 3 | preXOfAKindThreesCount == 3 | preXOfAKindFoursCount == 3 | preXOfAKindFivesCount == 3 | preXOfAKindSixesCount == 3) {
				preFullHouse = 25;
			}
		} else if (preXOfAKindTwosCount == 2) {
			if (preXOfAKindOnesCount == 3 | preXOfAKindThreesCount == 3 | preXOfAKindFoursCount == 3 | preXOfAKindFivesCount == 3 | preXOfAKindSixesCount == 3) {
				preFullHouse = 25;
			}
		} else if (preXOfAKindThreesCount == 2) {
			if (preXOfAKindOnesCount == 3 | preXOfAKindTwosCount == 3 | preXOfAKindFoursCount == 3 | preXOfAKindFivesCount == 3 | preXOfAKindSixesCount == 3) {
				preFullHouse = 25;
			}
		} else if (preXOfAKindFoursCount == 2) {
			if (preXOfAKindOnesCount == 3 | preXOfAKindTwosCount == 3 | preXOfAKindThreesCount == 3 | preXOfAKindFivesCount == 3 | preXOfAKindSixesCount == 3) {
				preFullHouse = 25;
			}
		} else if (preXOfAKindFivesCount == 2) {
			if (preXOfAKindOnesCount == 3 | preXOfAKindTwosCount == 3 | preXOfAKindThreesCount == 3 | preXOfAKindFoursCount == 3 | preXOfAKindSixesCount == 3) {
				preFullHouse = 25;
			}
		} else if (preXOfAKindSixesCount == 2) {
			if (preXOfAKindOnesCount == 3 | preXOfAKindTwosCount == 3 | preXOfAKindThreesCount == 3 | preXOfAKindFoursCount == 3 | preXOfAKindFivesCount == 3) {
				preFullHouse = 25;
			}
		}

		// A chance meets any condition, and its score is simply the sum of all the dies
		int preChance = 0;
		for (int i = 0; i < keepDiesVector.size(); i++) { // for each entry in the keepDiesVector
			preChance += stoi(keepDiesVector.at(i));
		}

		// show the updated score card with all the scores corresponding for each combination, and ask the player which combination they want to pick
		cout << endl << "Your score card" << endl;
		cout << "---------------" << endl;
		if (onesCombination > 0) { // don't show the pre-calculated score for a combination that has already been used before
			cout << "Ones: " << onesCombination << endl;
		} else if (onesCombination == -1) {
			cout << "Ones: 0" << endl;
		} else {
			cout << "Ones: " << preOnes << "*" << endl; // show the pre-calculated score for this combination if picked by the player and not already used yet
		}

		if (twosCombination > 0) {
			cout << "Twos: " << twosCombination << endl;
		} else if (twosCombination == -1) {
			cout << "Twos: 0" << endl;
		} else {
			cout << "Twos: " << preTwos << "*" << endl;
		}

		if (threesCombination > 0) {
			cout << "Threes: " << threesCombination << endl;
		} else if (threesCombination == -1) {
			cout << "Threes: 0" << endl;
		} else {
			cout << "Threes: " << preThrees << "*" << endl;
		}

		if (foursCombination > 0) {
			cout << "Fours: " << foursCombination << endl;
		} else if (foursCombination == -1) {
			cout << "Fours: 0" << endl;
		} else {
			cout << "Fours: " << preFours << "*" << endl;
		}

		if (fivesCombination > 0) {
			cout << "Fives: " << fivesCombination << endl;
		} else if (fivesCombination == -1) {
			cout << "Fives: 0" << endl;
		} else {
			cout << "Fives: " << preFives << "*" << endl;
		}

		if (sixesCombination > 0) {
			cout << "Sixes: " << sixesCombination << endl;
		} else if (sixesCombination == -1) {
			cout << "Sixes: 0" << endl;
		} else {
			cout << "Sixes: " << preSixes << "*" << endl;
		}

		// todo: the other kinds of combinations
		cout << "Sum: " << sumCombination << endl;
		cout << "Bonus: " << bonusCombination << endl;

		if (threeOfAKindCombination > 0) {
			cout << "Three of a kind: " << threeOfAKindCombination << endl;
		} else if (threeOfAKindCombination == -1) {
			cout << "Three of a kind: 0" << endl;
		} else {
			cout << "Three of a kind: " << preThreeOfAKind << "*" << endl;
		}

		if (fourOfAKindCombination > 0) {
			cout << "Four of a kind: " << fourOfAKindCombination << endl;
		} else if (fourOfAKindCombination == -1) {
			cout << "Four of a kind: 0" << endl;
		} else {
			cout << "Four of a kind: " << preFourOfAKind << "*" << endl;
		}

		if (fullHouseCombination > 0) {
			cout << "Full house: " << fullHouseCombination << endl;
		} else if (fullHouseCombination == -1) {
			cout << "Full house: 0" << endl;
		} else {
			cout << "Full house: " << preFullHouse << "*" << endl;
		}

		if (smallStraightCombination > 0) {
			cout << "Small straight: " << smallStraightCombination << endl;
		} else if (smallStraightCombination == -1) {
			cout << "Small straight: 0" << endl;
		} else {
			cout << "Small straight: " << preSmallStraight << "*" << endl;
		}

		if (largeStraightCombination > 0) {
			cout << "Large straight: " << largeStraightCombination << endl;
		} else if (largeStraightCombination == -1) {
			cout << "Large straight: 0" << endl;
		} else {
			cout << "Large straight: " << preLargeStraight << "*" << endl;
		}

		if (chanceCombination > 0) {
			cout << "Chance: " << chanceCombination << endl;
		} else if (chanceCombination == -1) {
			cout << "Chance: 0" << endl;
		} else {
			cout << "Chance: " << preChance << "*" << endl;
		}

		if (yahtzeeCombination > 0) {
			cout << "Yahtzee: " << yahtzeeCombination << endl;
		} else if (yahtzeeCombination == -1) {
			cout << "Yahtzee: 0" << endl;
		} else {
			cout << "Yahtzee: " << preYahtzee << "*" << endl;
		}

		// Currently, this is only calculated at the end of the game. In the future, this may be changed to allow for it to be calculated as the game is played.
		cout << "Total score: " << totalScore << endl;

		// Ask the user what combination they want to use (if any)
		repromptCombinationChoice:
		cout << endl << "Pick a combination to continue. If you don't want to pick a combination, enter \"0\"." << endl;
		cout << "For example, to pick the \"Ones\" combination, enter either \"1s\" or \"Ones\"." << endl;
		cout << "Enter a combination: ";
		string roundCombinationChoice;
		cin >> roundCombinationChoice;
		cout << endl;

		if (roundCombinationChoice == "0" | roundCombinationChoice == "no" | roundCombinationChoice == "No" | roundCombinationChoice == "none" | roundCombinationChoice == "None") { // TODO: case-insensitive string comparison
			cout << "Okay, ending the round with no combination chosen." << endl;

		} else if (roundCombinationChoice == "1s" | roundCombinationChoice == "Ones" | roundCombinationChoice == "ones") {
			if (onesCombination == -1 | onesCombination > 0) { // don't allow a combination to be chosen again if it has already been chosen before
				cout << "Sorry, you can only choose a combination you haven't already used. Pick another combination or enter \"0\" to pick no combination." << endl;
				goto repromptCombinationChoice;
			} else {
				if (preOnes == 0) { // if the player has picked a combination with a score of 0, show the score as 0 to the player but let the game take into account that this combination has now been picked so that it cannot be picked again.
					onesCombination = -1;
				} else {
					onesCombination = preOnes;
				}
				cout << "You have chosen the \"Ones\" combination and its score has been added to your scorecard." << endl;
			}

		} else if (roundCombinationChoice == "2s" | roundCombinationChoice == "Twos" | roundCombinationChoice == "twos") {
			if (twosCombination == -1 | twosCombination > 0) {
				cout << "Sorry, you can only choose a combination you haven't already used. Pick another combination or enter \"0\" to pick no combination." << endl;
				goto repromptCombinationChoice;
			} else {
				if (preTwos == 0) {
					twosCombination = -1;
				} else {
					twosCombination = preTwos;
				}
				cout << "You have chosen the \"Twos\" combination and its score has been added to your scorecard." << endl;
			}

		} else if (roundCombinationChoice == "3s" | roundCombinationChoice == "Threes" | roundCombinationChoice == "threes") {
			if (threesCombination == -1 | threesCombination > 0) {
				cout << "Sorry, you can only choose a combination you haven't already used. Pick another combination or enter \"0\" to pick no combination." << endl;
				goto repromptCombinationChoice;
			} else {
				if (preThrees == 0) {
					threesCombination = -1;
				} else {
					threesCombination = preThrees;
				}
				cout << "You have chosen the \"Threes\" combination and its score has been added to your scorecard." << endl;
			}

		} else if (roundCombinationChoice == "4s" | roundCombinationChoice == "Fours" | roundCombinationChoice == "fours") {
			if (foursCombination == -1 | foursCombination > 0) { // don't allow a combination to be chosen again if it has already been chosen before
				cout << "Sorry, you can only choose a combination you haven't already used. Pick another combination or enter \"0\" to pick no combination." << endl;
				goto repromptCombinationChoice;
			} else {
				if (preFours == 0) {
					foursCombination = -1;
				} else {
					foursCombination = preFours;
				}
				cout << "You have chosen the \"Fours\" combination and its score has been added to your scorecard." << endl;
			}

		} else if (roundCombinationChoice == "5s" | roundCombinationChoice == "Fives" | roundCombinationChoice == "fives") {
			if (fivesCombination == -1 | fivesCombination > 0) { // don't allow a combination to be chosen again if it has already been chosen before
				cout << "Sorry, you can only choose a combination you haven't already used. Pick another combination or enter \"0\" to pick no combination." << endl;
				goto repromptCombinationChoice;
			} else {
				if (preFives == 0) {
					fivesCombination = -1;
				} else {
					fivesCombination = preFives;
				}
				cout << "You have chosen the \"Fives\" combination and its score has been added to your scorecard." << endl;
			}

		} else if (roundCombinationChoice == "6s" | roundCombinationChoice == "Sixes" | roundCombinationChoice == "sixes") {
			if (sixesCombination == -1 | sixesCombination > 0) { // don't allow a combination to be chosen again if it has already been chosen before
				cout << "Sorry, you can only choose a combination you haven't already used. Pick another combination or enter \"0\" to pick no combination." << endl;
				goto repromptCombinationChoice;
			} else {
				if (preSixes == 0) {
					sixesCombination = -1;
				} else {
					sixesCombination = preSixes;
				}
				cout << "You have chosen the \"Sixes\" combination and its score has been added to your scorecard." << endl;
			}

		} else if (roundCombinationChoice == "3ofakind" | roundCombinationChoice == "threeofakind" | roundCombinationChoice == "3OfAKind" | roundCombinationChoice == "ThreeOfAKind") {
			if (threeOfAKindCombination == -1 | threeOfAKindCombination > 0) {
				cout << "Sorry, you can only choose a combination you haven't already used. Pick another combination or enter \"0\" to pick no combination." << endl;
				goto repromptCombinationChoice;
			} else {
				if (preThreeOfAKind == 0) {
					threeOfAKindCombination = -1;
				} else {
					threeOfAKindCombination = preThreeOfAKind;
				}
				cout << "You have chosen the \"Three of a kind\" combination and its score has been added to your scorecard." << endl;
			}

		} else if (roundCombinationChoice == "4ofakind" | roundCombinationChoice == "fourofakind" | roundCombinationChoice == "4OfAKind" | roundCombinationChoice == "FourOfAKind") {
			if (fourOfAKindCombination == -1 | fourOfAKindCombination > 0) {
				cout << "Sorry, you can only choose a combination you haven't already used. Pick another combination or enter \"0\" to pick no combination." << endl;
				goto repromptCombinationChoice;
			} else {
				if (preFourOfAKind == 0) {
					fourOfAKindCombination = -1;
				} else {
					fourOfAKindCombination = preFourOfAKind;
				}
				cout << "You have chosen the \"Four of a kind\" combination and its score has been added to your scorecard." << endl;
			}

		} else if (roundCombinationChoice == "fullhouse" | roundCombinationChoice == "Fullhouse" | roundCombinationChoice == "fullHouse" | roundCombinationChoice == "FullHouse") {
			if (fullHouseCombination == -1 | fullHouseCombination > 0) {
				cout << "Sorry, you can only choose a combination you haven't already used. Pick another combination or enter \"0\" to pick no combination." << endl;
				goto repromptCombinationChoice;
			} else {
				if (preFullHouse == 0) {
					fullHouseCombination = -1;
				} else {
					fullHouseCombination = preFullHouse;
				}
				cout << "You have chosen the \"Full house\" combination and its score has been added to your scorecard." << endl;
			}

		} else if (roundCombinationChoice == "smallstraight" | roundCombinationChoice == "Smallstraight" | roundCombinationChoice == "smallStraight" | roundCombinationChoice == "SmallStraight") {
			if (smallStraightCombination == -1 | smallStraightCombination > 0) {
				cout << "Sorry, you can only choose a combination you haven't already used. Pick another combination or enter \"0\" to pick no combination." << endl;
				goto repromptCombinationChoice;
			} else {
				if (preSmallStraight == 0) {
					smallStraightCombination = -1;
				} else {
					smallStraightCombination = preSmallStraight;
				}
				cout << "You have chosen the \"Small straight\" combination and its score has been added to your scorecard." << endl;
			}

		} else if (roundCombinationChoice == "largestraight" | roundCombinationChoice == "Largestraight" | roundCombinationChoice == "largeStraight" | roundCombinationChoice == "LargeStraight") {
			if (largeStraightCombination == -1 | largeStraightCombination > 0) {
				cout << "Sorry, you can only choose a combination you haven't already used. Pick another combination or enter \"0\" to pick no combination." << endl;
				goto repromptCombinationChoice;
			} else {
				if (preLargeStraight == 0) {
					largeStraightCombination = -1;
				} else {
					largeStraightCombination = preLargeStraight;
				}
				cout << "You have chosen the \"Large straight\" combination and its score has been added to your scorecard." << endl;
			}

		} else if (roundCombinationChoice == "chance" | roundCombinationChoice == "Chance") {
			if (chanceCombination == -1 | chanceCombination > 0) {
				cout << "Sorry, you can only choose a combination you haven't already used. Pick another combination or enter \"0\" to pick no combination." << endl;
				goto repromptCombinationChoice;
			} else {
				if (preChance == 0) {
					chanceCombination = -1;
				} else {
					chanceCombination = preChance;
				}
				cout << "You have chosen the \"Chance\" combination and its score has been added to your scorecard." << endl;
			}

		} else if (roundCombinationChoice == "yahtzee" | roundCombinationChoice == "Yahtzee") {
			if (chanceCombination == -1 | chanceCombination > 0) {
				cout << "Sorry, you can only choose a combination you haven't already used. Pick another combination or enter \"0\" to pick no combination." << endl;
				goto repromptCombinationChoice;
			} else {
				if (preYahtzee == 0) {
					yahtzeeCombination = -1;
				} else {
					yahtzeeCombination = preYahtzee;
				}
				cout << "You have chosen the \"Yahtzee\" combination and its score has been added to your scorecard." << endl;
			}

		} else {
			cout << "The combination chosen wasn't recognised. Please try again." << endl;
			goto repromptCombinationChoice;
		}

		pause(); // pause it before looping infinitely once all the dies have been selected
		return to_string(onesCombination) + "," + to_string(twosCombination) + "," + to_string(threesCombination) + "," + to_string(foursCombination) + "," + to_string(fivesCombination) + "," + to_string(sixesCombination) + "," +
			   to_string(sumCombination) + "," + to_string(bonusCombination) + "," + to_string(threeOfAKindCombination) + "," + to_string(fourOfAKindCombination) + "," + to_string(fullHouseCombination) + "," +
			   to_string(smallStraightCombination) + "," + to_string(largeStraightCombination) + "," + to_string(chanceCombination) + "," + to_string(yahtzeeCombination) + "," + to_string(totalScore); // return the results of the round back to the caller as a CSV-formatted string
			   // 1s, 2s, 3s, 4s, 5s, 6s, sum, bonus, 3OfKind, 4OfKind, fullHouse, smallStraight, largeStraight, chance, yahtzee, totalScore
	}
	goto continuePlayer1Round;
}

void startSPGame(bool debugMode) {
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

	int roundCount = 0;

	int rollCount = 0;
	string varsStr = "";

	vector<string> varsStrVector;

	cout << endl << "Yahtzee singleplayer" << endl;
	cout << "====================" << endl;
	cout << "Welcome to Yahtzee! For instructions, please consult the user manual." << endl;

newRoundPlayer1:
	roundCount++;
	cout << endl << endl;
	cout << endl << "*******" << endl;
	cout << "Round " << roundCount;
	cout << endl << "*******";
	varsStr = startPlayer1Round(debugMode, onesCombination, twosCombination, threesCombination, foursCombination, fivesCombination, sixesCombination,
								sumCombination, bonusCombination, threeOfAKindCombination, fourOfAKindCombination, fullHouseCombination,
								smallStraightCombination, largeStraightCombination, chanceCombination, yahtzeeCombination, totalScore, rollCount);

	varsStrVector = split(varsStr, ',');

	if (debugMode) { // show what each split result is before proceeding if debugMode is enabled
		for (int i = 0; i < varsStrVector.size(); i++) {
			debugMsg(0, "keepDiesVector.at(", i, ") = ", false);
			cout << varsStrVector.at(i) << endl;
		}
		pause();
	}

	// 1s, 2s, 3s, 4s, 5s, 6s, sum, bonus, 3OfKind, 4OfKind, fullHouse, smallStraight, largeStraight, chance, yahtzee, totalScore
	onesCombination = stoi(varsStrVector.at(0)); // convert the string inside the vector to an int using the stoi function, then put it into its appropriate variable
	twosCombination = stoi(varsStrVector.at(1));
	threesCombination = stoi(varsStrVector.at(2));
	foursCombination = stoi(varsStrVector.at(3));
	fivesCombination = stoi(varsStrVector.at(4));
	sixesCombination = stoi(varsStrVector.at(5));
	sumCombination = stoi(varsStrVector.at(6));
	bonusCombination = stoi(varsStrVector.at(7));
	threeOfAKindCombination = stoi(varsStrVector.at(8));
	fourOfAKindCombination = stoi(varsStrVector.at(9));
	fullHouseCombination = stoi(varsStrVector.at(10));
	smallStraightCombination = stoi(varsStrVector.at(11));
	largeStraightCombination = stoi(varsStrVector.at(12));
	chanceCombination = stoi(varsStrVector.at(13));
	yahtzeeCombination = stoi(varsStrVector.at(14));
	totalScore = stoi(varsStrVector.at(15));

	varsStr = ""; // clear the varsStr so it's ready for the next round
	varsStrVector.clear(); // also clear the varsStrVector so it's ready for the next round, too

	if (roundCount < 5) {
		goto newRoundPlayer1;
	} else {
		// all rounds have been played. calculate and show the final scores.
		
		// first off, get any combinations where the score was zero but the combination was chosen by the player anyway, and set them all back to a score of zero to make calculating the final result easier
		if (onesCombination == -1) {
			onesCombination = 0;
		}
		if (twosCombination == -1) {
			twosCombination = 0;
		}
		if (threesCombination == -1) {
			threesCombination = 0;
		}
		if (foursCombination == -1) {
			foursCombination = 0;
		}
		if (fivesCombination == -1) {
			fivesCombination = 0;
		}
		if (sixesCombination == -1) {
			sixesCombination = 0;
		}
		if (threeOfAKindCombination == -1) {
			threeOfAKindCombination = 0;
		}
		if (fourOfAKindCombination == -1) {
			fourOfAKindCombination = 0;
		}
		if (fullHouseCombination == -1) {
			fullHouseCombination = 0;
		}
		if (chanceCombination == -1) {
			chanceCombination = 0;
		}
		if (yahtzeeCombination == -1) {
			yahtzeeCombination = 0;
		}

		totalScore = onesCombination + twosCombination + threesCombination + foursCombination + fivesCombination + sixesCombination + threeOfAKindCombination + fourOfAKindCombination + fullHouseCombination + chanceCombination + yahtzeeCombination;

		cout << endl << "Game finished! Your final score is: " << totalScore << "." << endl;
		pause();
		return;
	}
}

void startMPGame(bool debugMode) {
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

	int roundCount = 0;

	int rollCount = 0;
	string varsStr = "";

	vector<string> varsStrVector;

	cout << endl << "Yahtzee multiplayer" << endl;
	cout << "===================" << endl;
	cout << "Welcome to Yahtzee! For instructions, please consult the user manual." << endl;
	cout << "Player 1 goes first, then Player 2. The scores of both players will then be shown together.";

newRoundPlayer1:
	roundCount++;
	cout << endl << endl;
	cout << endl << "*P1****" << endl;
	cout << "Round " << roundCount;
	cout << endl << "*******";
	varsStr = startPlayer1Round(debugMode, onesCombination, twosCombination, threesCombination, foursCombination, fivesCombination, sixesCombination,
		sumCombination, bonusCombination, threeOfAKindCombination, fourOfAKindCombination, fullHouseCombination,
		smallStraightCombination, largeStraightCombination, chanceCombination, yahtzeeCombination, totalScore, rollCount);

	varsStrVector = split(varsStr, ',');

	if (debugMode) { // show what each split result is before proceeding if debugMode is enabled
		for (int i = 0; i < varsStrVector.size(); i++) {
			debugMsg(0, "keepDiesVector.at(", i, ") = ", false);
			cout << varsStrVector.at(i) << endl;
		}
		pause();
	}

	// 1s, 2s, 3s, 4s, 5s, 6s, sum, bonus, 3OfKind, 4OfKind, fullHouse, smallStraight, largeStraight, chance, yahtzee, totalScore
	onesCombination = stoi(varsStrVector.at(0)); // convert the string inside the vector to an int using the stoi function, then put it into its appropriate variable
	twosCombination = stoi(varsStrVector.at(1));
	threesCombination = stoi(varsStrVector.at(2));
	foursCombination = stoi(varsStrVector.at(3));
	fivesCombination = stoi(varsStrVector.at(4));
	sixesCombination = stoi(varsStrVector.at(5));
	sumCombination = stoi(varsStrVector.at(6));
	bonusCombination = stoi(varsStrVector.at(7));
	threeOfAKindCombination = stoi(varsStrVector.at(8));
	fourOfAKindCombination = stoi(varsStrVector.at(9));
	fullHouseCombination = stoi(varsStrVector.at(10));
	smallStraightCombination = stoi(varsStrVector.at(11));
	largeStraightCombination = stoi(varsStrVector.at(12));
	chanceCombination = stoi(varsStrVector.at(13));
	yahtzeeCombination = stoi(varsStrVector.at(14));
	totalScore = stoi(varsStrVector.at(15));

	varsStr = ""; // clear the varsStr so it's ready for the next round
	varsStrVector.clear(); // also clear the varsStrVector so it's ready for the next round, too

	if (roundCount < 2) {
		goto newRoundPlayer1;
	} else {
		// all rounds have been played. calculate and show the final scores.

		// first off, get any combinations where the score was zero but the combination was chosen by the player anyway, and set them all back to a score of zero to make calculating the final result easier
		if (onesCombination == -1) {
			onesCombination = 0;
		}
		if (twosCombination == -1) {
			twosCombination = 0;
		}
		if (threesCombination == -1) {
			threesCombination = 0;
		}
		if (foursCombination == -1) {
			foursCombination = 0;
		}
		if (fivesCombination == -1) {
			fivesCombination = 0;
		}
		if (sixesCombination == -1) {
			sixesCombination = 0;
		}
		if (threeOfAKindCombination == -1) {
			threeOfAKindCombination = 0;
		}
		if (fourOfAKindCombination == -1) {
			fourOfAKindCombination = 0;
		}
		if (fullHouseCombination == -1) {
			fullHouseCombination = 0;
		}
		if (chanceCombination == -1) {
			chanceCombination = 0;
		}
		if (yahtzeeCombination == -1) {
			yahtzeeCombination = 0;
		}

		totalScore = onesCombination + twosCombination + threesCombination + foursCombination + fivesCombination + sixesCombination + threeOfAKindCombination + fourOfAKindCombination + fullHouseCombination + chanceCombination + yahtzeeCombination;

		cout << endl << "Player 1's game finished! Player 1's final score is: " << totalScore << "." << endl;
		int player1TotalScore = totalScore;
		cout << "Player 2's game is up next... Good luck!" << endl;
		pause();

		// clear all the variables in preparation for player 2's game.
		onesCombination = 0;
		twosCombination = 0;
		threesCombination = 0;
		foursCombination = 0;
		fivesCombination = 0;
		sixesCombination = 0;
		sumCombination = 0;
		bonusCombination = 0;
		threeOfAKindCombination = 0;
		fourOfAKindCombination = 0;
		fullHouseCombination = 0;
		smallStraightCombination = 0;
		largeStraightCombination = 0;
		chanceCombination = 0;
		yahtzeeCombination = 0;
		totalScore = 0;

		roundCount = 0;

		rollCount = 0;
		varsStr = "";

		varsStrVector.clear();
		totalScore = 0;

	newRoundPlayer2:
		roundCount++;
		cout << endl << endl;
		cout << endl << "*P2****" << endl;
		cout << "Round " << roundCount;
		cout << endl << "*******";
		varsStr = startPlayer1Round(debugMode, onesCombination, twosCombination, threesCombination, foursCombination, fivesCombination, sixesCombination,
			sumCombination, bonusCombination, threeOfAKindCombination, fourOfAKindCombination, fullHouseCombination,
			smallStraightCombination, largeStraightCombination, chanceCombination, yahtzeeCombination, totalScore, rollCount);

		varsStrVector = split(varsStr, ',');

		if (debugMode) { // show what each split result is before proceeding if debugMode is enabled
			for (int i = 0; i < varsStrVector.size(); i++) {
				debugMsg(0, "keepDiesVector.at(", i, ") = ", false);
				cout << varsStrVector.at(i) << endl;
			}
			pause();
		}

		// 1s, 2s, 3s, 4s, 5s, 6s, sum, bonus, 3OfKind, 4OfKind, fullHouse, smallStraight, largeStraight, chance, yahtzee, totalScore
		onesCombination = stoi(varsStrVector.at(0)); // convert the string inside the vector to an int using the stoi function, then put it into its appropriate variable
		twosCombination = stoi(varsStrVector.at(1));
		threesCombination = stoi(varsStrVector.at(2));
		foursCombination = stoi(varsStrVector.at(3));
		fivesCombination = stoi(varsStrVector.at(4));
		sixesCombination = stoi(varsStrVector.at(5));
		sumCombination = stoi(varsStrVector.at(6));
		bonusCombination = stoi(varsStrVector.at(7));
		threeOfAKindCombination = stoi(varsStrVector.at(8));
		fourOfAKindCombination = stoi(varsStrVector.at(9));
		fullHouseCombination = stoi(varsStrVector.at(10));
		smallStraightCombination = stoi(varsStrVector.at(11));
		largeStraightCombination = stoi(varsStrVector.at(12));
		chanceCombination = stoi(varsStrVector.at(13));
		yahtzeeCombination = stoi(varsStrVector.at(14));
		totalScore = stoi(varsStrVector.at(15));

		varsStr = ""; // clear the varsStr so it's ready for the next round
		varsStrVector.clear(); // also clear the varsStrVector so it's ready for the next round, too

		if (roundCount < 2) {
			goto newRoundPlayer2;
		} else {
			// all rounds have been played. calculate and show the final scores.

			// first off, get any combinations where the score was zero but the combination was chosen by the player anyway, and set them all back to a score of zero to make calculating the final result easier
			if (onesCombination == -1) {
				onesCombination = 0;
			}
			if (twosCombination == -1) {
				twosCombination = 0;
			}
			if (threesCombination == -1) {
				threesCombination = 0;
			}
			if (foursCombination == -1) {
				foursCombination = 0;
			}
			if (fivesCombination == -1) {
				fivesCombination = 0;
			}
			if (sixesCombination == -1) {
				sixesCombination = 0;
			}
			if (threeOfAKindCombination == -1) {
				threeOfAKindCombination = 0;
			}
			if (fourOfAKindCombination == -1) {
				fourOfAKindCombination = 0;
			}
			if (fullHouseCombination == -1) {
				fullHouseCombination = 0;
			}
			if (chanceCombination == -1) {
				chanceCombination = 0;
			}
			if (yahtzeeCombination == -1) {
				yahtzeeCombination = 0;
			}

			totalScore = onesCombination + twosCombination + threesCombination + foursCombination + fivesCombination + sixesCombination + threeOfAKindCombination + fourOfAKindCombination + fullHouseCombination + chanceCombination + yahtzeeCombination;

			cout << endl << "Player 2's game finished!" << endl;
			cout << endl << "Scores" << endl;
			cout << "------" << endl;
			cout << "Player 1: " << player1TotalScore << endl;
			cout << "Player 2: " << totalScore << endl;
			pause();
		}
	}

}

int main() {
	bool debugMode = false; // initialise the debugMode variable with a default value of false

	// Textart from http://www.patorjk.com/software/taag/#p=display&f=Standard&t=Yahtzee . Backslash characters were manually escaped in order to allow for it to display properly when ran.
	showMainMenuWithLogo:
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
		debugMsg(0, "menuResult: ", menuResult, "", true); // if debug mode is on, show the retrieved result from earlier
	}

	if (menuResult == 1) {
		startSPGame(debugMode);
	} else if (menuResult == 2) {
		startMPGame(debugMode);
	} else if (menuResult == 3) {
		cout << "Error: Unimplemented." << endl;
		goto showMainMenu;
	} else if (menuResult == 9) {
		return 0; // quit the game with a return code of 0 (application closing with no errors)
	}
	pause();
	goto showMainMenuWithLogo; // go back to the main menu after a game has finished
}