/**
 * Name: Yousef Al-Jazzazi 
 * netID: ya2225
 * Asssignment 1 for CPE class
 * Project name:  Civil Engineering Case Study � Aviation Safety
 * Description: The program checks whether the location detecting systems in airplanes are up to aviation safety standards. 
*/

#include "Assignment1.hpp"

using namespace std;

int main()
{
	cout << "This function of this program is to calculate the inaccuracy of an ariplane positioning system" << endl;
	cout << "The airplane store its positions using two different systems." << endl;
	cout << "The program checks the inaccuracy by calculating the differenct between the two systems." << endl;

	bool repeat = true;
	while(repeat)
		menu(repeat);

	return(0);
}

void menu(bool& repeat)
{
	
	cout << "There are two functions of the program."
		<< "\nPress 1 to calculate the error"
		<< "\nPress 2 to display the error. Display the error only after calculating it" 
		<< "\nPress 3 to exit the run" << endl;

	unsigned choice;

	cin >> choice;

	// assert(choice > 0 && choice <= 3, "Invalid input!");

	switch(choice)
	{
		case 1 : 
			calcError();
			break;
		
		case 2:
			displayError();
			break;

		case 3:
			cout << "Thanks for using our program." << endl;

		default:
			cout << "Invalid input! Enter a valid option." << endl;
			break;
	}

}		

void calcError()
{
	ifstream file1, file2;
	ofstream errLog;
	string nameFile;
	double tolerance(0);

	cout << "To calculate the error. Please enter the names of the two files that store the position of the airplane" << endl;
	cout << "Start by entering the name of the first file: (Press 0 to go back to the main menu)" << endl;
	cin >> nameFile;
	file1.open(nameFile, ios::in);

/**
 * if the name inputed by the user doesnt work, keep asking the user for a valid name.
 * The user can opt out by inputting a 0
*/
	while (file1.fail())
	{
		if (nameFile == "0")
			return;
		cerr << "Error. The file doesn't exist. Please try again" << endl;
		cin >> nameFile;

		file1.open(nameFile, ios::in);
	}

	cout << "Please enter the name of the second file: (Press 0 to go back to the main menu)" << endl;
	cin >> nameFile;
	file2.open(nameFile, ios::in);
/**
 * if the name inputed by the user doesnt work, keep asking the user for a valid name.
 * The user can opt out by inputting a 0
*/
	while (file2.fail())
	{
		if (nameFile == "0")
			exit(EXIT_FAILURE);
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
	while (file1 >> xfile1 >> yfile1 >> zfile1 && file2 >> xfile2 >> yfile2 >> zfile2)
	{
		double distance(0);
		// Because the airplane cannot be under the radar. If one of the heights is negative, the value -1 will be stored as the distance
		if (zfile1 < 0 || zfile2 < 0)
		{
			errLog << -1 << " " << time << "\n";
			// Time incremented by 0.25 because we know that the position is calculated every quarter of a second
			time += 0.25;
			continue;
		}
		// Equation of two points in a 3d coordinates
		// Derived from applying the pythagorean theorem twice
		distance = sqrt((xfile1 - xfile2) * (xfile1 - xfile2) + (yfile1 - yfile2) * (yfile1 - yfile2) + (zfile1 - zfile2) * (zfile1 - zfile2));
		
		//Only store in the error file if the distance is greater than the inputted tolerance value
		if (distance > abs(tolerance))
			errLog << distance << " " << time << "\n";
		time += 0.25;	
	}
	//Another while loop in case there are more values in one file
	//the distance will be stored as 0 indicating this scenario 
	while (file1.eof() != file2.eof())
	{
		file1 >> xfile1 >> yfile1 >> zfile1;
		file2 >> xfile2 >> yfile2 >> zfile2;
		errLog << 0 << " " << time << endl;
		time += 0.25;
	}

	// closing all the files
	file1.close();
	file2.close();
	errLog.close();	
}

void displayError()
{
	ifstream errLog;
	/**
	 * check link below for ::nocreate
	 * <https://www.linuxquestions.org/questions/programming-9/c-ios-nocreate-510563/>
	*/
	// errLog.open("ERR.LOG", ios::_Nocreate);

	errLog.open("ERR.LOG");

	//In case the error file has not been created 
	if (errLog.fail())
	{
		cerr << "File doesnt exist. Please calculate the error before displaying the error" << endl;
		exit(EXIT_FAILURE);
	}

	cout << left << setw(15) << "Time[s]" << setw(15) << "Distance[km]" << "\n";
	double distance(0), time(0);
	while (errLog >> distance >> time) 
		cout << left << setw(15) << time << setw(15) << distance << "\n";
	
	errLog.close();
}
