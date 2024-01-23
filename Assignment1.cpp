/*
Name: Yousef Al-Jazzazi 
netID: ya2225
Asssignment 1 for CPE class
Project name:  Civil Engineering Case Study – Aviation Safety
Description: The program checks whether the location detecting systems in airplanes are up to aviation safety standards. 

*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

//Initilizing functions
void menu(bool&);
void calcError();
void displayError();

int main() {
	cout << "This function of this program is to calculate the inaccuracy of an ariplane positioning system" 
		<< "\nThe airplane store its positions using two different systems."
		<< "The program checks the inaccuracy by calculating the differenct between the two systems" 
		<< endl;
	bool repeat = true;
	//we pass repeat variable as a pointer, so it can be modified from inside menu function
	while(repeat)
		menu(repeat);

	return(0);
}

//A function to display the menu and ask the user what function in the program they want to use (or whether they want to exit the program)
void menu(bool& repeat) {
	
	cout << "There are two functions of the program."
		<< "\nPress 1 to calculate the error"
		<< "\nPress 2 to display the error. Display the error only after calculating it" 
		<< "\nPress 3 to exit the run" << endl;
	//I choose the combination of string and if statement rather than an switch statement because 
	//in the case a user input a string in an int, it will result in a failed comand with an infinite loop
	string choice;
	cin >> choice;
	if (choice == "1")
		calcError();
	else if(choice == "2")
		displayError();
	else if (choice == "3") {
		cout << "Thanks for using our porgramm" << endl;
		//The menu function will be called continuesly until repeat is false which is when the user choice is 3
		repeat = false;
	}
	else
		cout << "Please input one of the options" << endl;

	}
		

//A function to calculating the error and storing them in a file
void calcError() {
	ifstream file1, file2;
	ofstream errLog;
	string nameFile;
	double tolerance(0);

	cout << "To calculate the error. Please enter the names of the two files that store the position of the airplane" << endl;
	cout << "Start by entering the name of the first file: (Press 0 to go back to the main menu)" << endl;
	cin >> nameFile; 
	file1.open(nameFile, ios::in);
	//if the name inputed by the user doesnt work, keep asking the user for a valid name.
	//The user can opt out by inputting a 0
	while (file1.fail()) {
		if (nameFile == "0")
			return;
		cerr << "Error. The file doesn't exist. Please try again" << endl;
		cin >> nameFile;
		file1.open(nameFile, ios::in);
		
	}
	
	cout << "Please enter the name of the second file: (Press 0 to go back to the main menu)" << endl;
	cin >> nameFile;
	file2.open(nameFile, ios::in);
	//if the name inputed by the user doesnt work, keep asking the user for a valid name.
	//The user can opt out by inputting a 0
	while (file2.fail()) {
		if (nameFile == "0")
			return;
		cerr << "Error. The file doesn't exist. Please try again" << endl;
		cin >> nameFile;
		file2.open(nameFile, ios::in);
		
	}

	errLog.open("ERR.LOG", ios::out);
	
	
	cout << "Please enter the magnitude of the accepted" << endl;
	cin >> tolerance;

	double xfile1(0), yfile1(0), zfile1(0);
	double xfile2(0), yfile2(0), zfile2(0);
	double time(0);
	while (file1 >> xfile1 >> yfile1 >> zfile1 && file2 >> xfile2 >> yfile2 >> zfile2) {
		
		double distance(0);
		//Because the airplane cannot be under the radar. If one of the heights is negative, the value -1 will be stored as the distance
		if (zfile1 < 0 || zfile2 < 0) {
			errLog << -1 << " " << time << "\n";
			//Time incremented by 0.25 because we know that the position is calculated ever quarter of a second
			time += 0.25;
			continue;
		}
		//Equation of two points in a 3d coordinates
		//Derived from applying the pythagorean theorem twice
		distance = sqrt((xfile1 - xfile2) * (xfile1 - xfile2) + (yfile1 - yfile2) * (yfile1 - yfile2) + (zfile1 - zfile2) * (zfile1 - zfile2));
		
		//Only store in the error file if the distance is greater than the inputted tolerance value
		if (distance > abs(tolerance))
			errLog << distance << " " << time << "\n";
		time += 0.25;
		
	}
	//Another while loop in case there are more values in one file
	//the distance will be stored as 0 indicating this scenario 
	while (file1.eof() != file2.eof()) {
		file1 >> xfile1 >> yfile1 >> zfile1;
		file2 >> xfile2 >> yfile2 >> zfile2;
		errLog << 0 << " " << time << "\n";
		time += 0.25;
	}

	//closing all the files
	file1.close();
	file2.close();
	errLog.close();
	
}

//A function to display the errors stored in the error file
void displayError() {
	ifstream errLog;
	errLog.open("ERR.LOG", ios::_Nocreate);
	
	//In case the error file has not been created 
	if (errLog.fail()) {
		cerr << "File doesnt exist. Please calculate the error before displaying the error\n\n\n" << endl;
		return;
	}

	cout << left << setw(15) << "Time[s]" << setw(15) << "Distance[km]" << "\n";
	double distance(0), time(0);
	while (errLog >> distance >> time) 
		cout << left << setw(15) << time << setw(15) << distance << "\n";
	
	errLog.close();

}