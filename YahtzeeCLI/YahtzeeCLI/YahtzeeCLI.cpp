 // YahtzeeCLI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>

using namespace std;

// https://stackoverflow.com/questions/21257544/c-wait-for-user-input
// http://www.cplusplus.com/doc/tutorial/functions/
void pause() {
	cout << "Press any key to continue . . . " << endl;
	_getch(); // needs conio.h, this function waits for a character input from terminal and then returns its value
	return;
}

int main()
{
	cout << "Hello world!" << endl;
	pause();
}

