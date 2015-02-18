#include "p2lex.h"
#include<iostream>
#include<string>

using namespace std;

int main(int argc, char* argv[]){
	
	istream *br;
	ifstream infile;

	infile.open(argv[1]);
	if( infile.is_open() ){
		br = &infile;
	}
	else{
		cerr << "Error: Could not open " << srting(argv[1]) << endl;
		return 1;
	}
	
	if(argc == 2){
		//get tokens from file
		infile.open(argv[1]);
		if( infile.is_open() ){
			br = &infile;
		}
		else{
			cerr << "Error: Could not open " << srting(argv[1]) << endl;
                	return 1;
	        }
	}
	else if(argc == 1){
		//get tokens from cmdln input
		string line;
		while( cin.good() && !done ){
			cin >> line;
			if(line == "done"){
				done = true;
				break;
			}
			cout << line << endl;
		}
	}
	else{
		cerr << "Error: Too many args" << endl;
		cerr << "This program takes either no args and reads user input \nor\n";
		cerr << "It can take 1 arg which is the name of a file it will read" << endl;
		return 1;
	}

return 0;
}


