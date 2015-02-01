#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

int main (int argc, char *argv[]) {
	istream *br;
	ifstream infile;

	if(argc != 3){
		cerr << "This program takes exeactly 2 arguments:\n";
		cerr << "The first is the ajdective to be added, the second is the file name.\n";
		return 0;
	}

	string adj = argv[1];
	infile.open(argv[2]);
	if(infile.is_open()){
		br = &infile;
		cout << "it worked" << endl;
	}
	else {
		cerr << "Error: Could not open" << string(argv[2]) << endl;
		return 1;
	}


    return 0;
}
