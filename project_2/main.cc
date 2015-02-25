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
		//getting tokens from cmdln input
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
	vector<string> IDs;
	vector<string> INTs;
	bool inVec = false;
	while( (t = getToken(br, lexeme)) != DONE){
		// Gets the tokens one at a time from the given input
		// then stores the lexeme to the list if appropiate.
		// NOTE:  all the cout statements are for testing porposes only
		if(t == ID){
			cout << "ID: " << lexeme << " " << endl;
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
				counters[t]++;
			}
			else{
				inVec = false;
			}
		}
		else if(t == PLUS || t == MINUS || t == SLASH || t == STAR){
			cout << "MATH" << endl;
			counters[t]++;
		}
		else if(t == SC){
			cout << "semi-colon" << endl;
			counters[t]++;
		}
		else if(t == INT){
			cout << "INT: " << lexeme << endl;
			INTs.push_back(lexeme);
			counters[t]++;
		}
		else if(t == DONE){
			cout << "THATS IT BABY" << endl;
			counters[t]++;
		}
		else if(t == STRING){
			cout << "STRING: " << lexeme << endl;
			counters[t]++;
		}
		else if(t == SET){
			cout << "setting!" << endl;
			counters[t]++;
		}
		else if(t == PRINT){
			cout << "printing!" << endl;
			counters[t]++;
		}

	}

	if(br->good()){
		cerr << endl << "Error: encountered lexically incorrect statement." << endl;
	}
	cout << endl;

	cout << "ID     : " << counters[ID]     << endl;
	cout << "INT    : " << counters[INT]    << endl;
	cout << "STRING : " << counters[STRING] << endl;
	cout << "PLUS   : " << counters[PLUS]   << endl;
	cout << "MINUS  : " << counters[MINUS]  << endl;
	cout << "STAR   : " << counters[STAR]   << endl;
	cout << "SLASH  : " << counters[SLASH]  << endl;
	cout << "SET    : " << counters[SET]    << endl;
	cout << "PRINT  : " << counters[PRINT]  << endl;
	cout << "SC     : " << counters[SC]     << endl;
	cout << "DONE   : 1"<< endl << endl;

	cout << "The unique IDs were ";
	for (int i = 0; i<IDs.size(); i++){
		cout << IDs[i] << " ";
	}
	cout << endl;

	cout << "The ints found were ";
	for (int i = 0; i<INTs.size(); i++){
		cout << INTs[i] << " ";
	}
	cout << endl << endl;
return 0;
}
