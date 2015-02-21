#include "p2lex.h"
#include<iostream>
#include<string>
#include<fstream>
#include<map>

using namespace std;

int main(int argc, char* argv[]){
	
	istream *br;
	ifstream infile;
	string lexeme;

	if(argc == 2){
		//get tokens from file
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
		//get tokens from cmdln input
		br = &cin;
	}
	else{
		cerr << "Error: Too many args" << endl;
		cerr << "This program takes either no args and reads user input or\n";
		cerr << "It can take 1 arg which is the name of a file it will read" << endl;
		return 1;
	}
	
	map<Token, int> counters;
	Token t;
	while( (t = getToken(br, lexeme)) != DONE){
		cout << lexeme;
		counters[t]++;
		lexeme = "";
	}
	
	map<Token, int>::iterator it;
	for(it = counters.begin(); it != counters.end(); it++){
		cout << it->first << ":" << it->second << endl;
	}
	//Token t = getToken(br, lexeme);

return 0;
}
