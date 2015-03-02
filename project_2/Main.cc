#include "p2lex.h"
#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<vector>

using namespace std;

int main(int argc, char* argv[]){
	
	istream *br;
	ifstream infile;
	string lexeme;

	if(argc == 2){
		//getting tokens from file
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
		//getting tokens from standard user input
		br = &cin;
	}
	else{
		cerr << "Error: Too many args" << endl;
		cerr << "This program takes either no args and reads standard user input or\n";
		cerr << "It can take 1 arg which is the name of a file it will read" << endl;
		return 1;
	}
	
	map<Token, int> counters;
	Token t;
	vector<string> IDs;
	vector<string> INTs;
	bool inVec = false;
	while( (t = getToken(br, lexeme)) != DONE){
		// Gets the tokens one at a time from the given input
		// then stores the lexeme to the list if appropiate.
		// NOTE:  all the cout statements are for testing porposes only
		if(t == ID){
			for(int i = 0; i < IDs.size(); i++){
				if(IDs[i] == lexeme){
					// Tests if the ID has been found already
					// if it has then it will not be added to the 
					// list otherwise it will.
					inVec = true;
					break;
				}
			}
			if(!inVec){
				IDs.push_back(lexeme);
			}
			else{
				inVec = false;
			}
			counters[t]++;
		}
		else{
			counters[t]++;
		}
	}

	if(counters[ID] != 0)
		cout << "Identifier:" << counters[ID] << endl;
	if(counters[INT] != 0)
		cout << "Integer constant:" << counters[INT] << endl;
	if(counters[STRING] != 0)
		cout << "Quoted string:" << counters[STRING] << endl;
	if(counters[PLUS] != 0)
		cout << "+ operator:" << counters[PLUS] << endl;
	if(counters[MINUS] != 0)
		cout << "- operator:" << counters[MINUS] << endl;
	if(counters[STAR] != 0)
		cout << "* operator:" << counters[STAR] << endl;
	if(counters[SLASH] != 0)
		cout << "/ operator:" << counters[SLASH] << endl;
	if(counters[SET] != 0)
		cout << "set keyword:" << counters[SET] << endl;
	if(counters[PRINT] != 0)
		cout << "print keyword:" << counters[PRINT] << endl;
	if(counters[SC] != 0)
		cout << "semicolon:" << counters[SC] << endl;
	
	if(IDs.size() != 0){
		cout << "List of identifiers: ";
		for (int i = 0; i < IDs.size()-1 ; i++){
			cout << IDs[i] << ", ";
		}
		cout << IDs[IDs.size()-1] << endl;
	}

return 0;
}
