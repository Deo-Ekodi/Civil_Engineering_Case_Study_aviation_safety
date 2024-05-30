/**
 * created header file for:
 * 1. all function declarations
 * 2. all header files
*/

#pragma once


#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
// #include <cassert>
#include <cstdlib>

void menu(bool&);		// display the menu and ask the user what function in the program they want to use (or whether they want to exit the program)
void calcError();		// calculating the error and storing them in a file
void displayError();	// display the errors stored in the error file
void menu(bool& repeat);
void calcError();
void displayError();
