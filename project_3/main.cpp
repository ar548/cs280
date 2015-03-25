#include "p2lex.h"
#include "classes.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){

	istream *br;
	ifstream infile;
	string lex;
	
	if(argc == 2){
		//gets the input from a file
		infile.open(argv[1]);
		if( infile.is_open() ){
			br = &infile;
		}
		else{
			cerr << "Error: Could not open " << string(argv[1]) << endl;
			return 1;
		}
	}
	else if(argc == 1){
		//gets standard user input
		br = &cin;
	}
	else{
		cerr << "Error: Too many args" << endl;
		cerr << "This program takes either no args and reads standard user input or\n";
		cerr << "It can take 1 arg which is the name of a file it will read\n";
		return 1;
	}

	program prg(br, lex);

return 0;
}
