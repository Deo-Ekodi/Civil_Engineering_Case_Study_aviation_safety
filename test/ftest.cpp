#include <fstream>
#include <iostream>

using namespace std;

int main(){
	ifstream f1;
	f1.open("f1.txt", fstream::in);
	f1 << "hello,i\'m f1";

	f1.close();
	
	ofstream f2;
	f2.open("f1.txt", fstream::out);
	if(!f2){
		cerr << "err.. could not open file" << endl;
		exit(EXIT_FAILURE);
	}
	;

	return EXIT_SUCCESS;
}
