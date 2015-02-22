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
	vector<string> IDs;
	vector<string> INTs;
	bool inVec = false;
	while( (t = getToken(br, lexeme)) != DONE){
		if(t == ID){
			cout << "ID: " << lexeme << " " << endl;
			for(int i = 0; i < IDs.size(); i++){
				if(IDs[i] == lexeme){
					inVec = true;
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
		else if(t == DONE)
			cout << "THATS IT BABY" << endl;

	}

	map<Token, int>::iterator it;
	//for(it = counters.begin(); it != counters.end(); it++){
	//	cout << it->first << ":" << it->second << endl;
	//}
	
	cout << "ID     : " << counters[ID] << endl;
	cout << "INT    : " << counters[INT] << endl;
	cout << "STRING : " << counters[STRING] << endl;
	cout << "PLUS   : " << counters[PLUS] << endl;
	cout << "MINUS  : " << counters[MINUS] << endl;
	cout << "STAR   : " << counters[STAR] <<endl;
	cout << "SLASH  : " << counters[SLASH] << endl;
	cout << "SET    : " << counters[SET] << endl;
	cout << "PRINT  : " << counters[PRINT] << endl;
	cout << "SC     : " << counters[SC] << endl;
	cout << "DONE   : 1"<< endl;

	cout << "The unique IDs were ";
	for (int i = 0; i<IDs.size(); i++){
		cout << IDs[i] << " ";
	}
	cout << endl;

	cout << "The ints found were ";
	for (int i = 0; i<INTs.size(); i++){
		cout << INTs[i] << " ";
	}
	cout << endl;
return 0;
}

Token getToken(istream *br, string &lexeme){
	Token T;
	lexeme = "";
	char ch;
	if(br->good()){
		while(br->good()){
			ch = br->get();
			if(ch == '+'){
				T = PLUS;
				break;
			}
			else if(ch == '-'){
				T = MINUS;
				break;
			}
			else if(ch == '*'){
				T = STAR;
				break;
			}
			else if(ch == '/'){
				if(br->peek() == '/'){
					do{
						ch = br->get();
					}while(ch != '\n');
					continue;
				}
				else{
					T = SLASH;
				}
				break;
			}
			else if(ch == ';'){
				T = SC;
				break;
			}
			else if(ch == '"'){
				T = STRING;
				ch = br->get();
				lexeme += ch;
				while(ch != '"'){
					ch = br->get();
					if (ch == '\n'){
						T = DONE;
						return T;
					}
					lexeme += ch;
				}
				cout << "The string recognised was: \"" << lexeme  << endl;
				break;
			}
			else if( (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ){
				lexeme += ch;
				while( (br->peek() >= 'A' && br->peek() <= 'Z') || (br->peek() >= 'a' && br->peek() <= 'z') ){
					ch = br->get();
					lexeme += ch;
				}
				if(lexeme == "set"){
					T = SET;
					return SET;
				}
				else if(lexeme == "print"){
					T = PRINT;
					return T;
				}
				else{
					T = ID;
					return T;
				}
			}
			else if( (ch >= '0' && ch <= '9') ){
				T = INT;
				lexeme += ch;
				while(br->peek() >= '0' && br->peek() <= '9'){
					ch = br->get();
					lexeme += ch;
				}
				break;
			}
		}
	}
	else{
		T = DONE;
	}
	return T;
}
