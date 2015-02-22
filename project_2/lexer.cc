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
		//cout << lexeme << endl;
		if(t == ID)
			cout << lexeme << endl;
		else if(t == PLUS || t == MINUS || t == SLASH || t == STAR)
			cout << "MATH" << endl;
		else if(t == SC)
			cout << "semi-colon" << endl;
		else if(t == INT)
			cout << "INT" << endl;
		else if(t == DONE)
			cout << "THATS IT BABY" << endl;

		counters[t]++;
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
	cout << "DONE   : " << counters[DONE] << endl;


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
						break;
					}
					lexeme += ch;
				}
				cout << "The string recognised was: \"" << lexeme  << endl;
				break;
			}
			else if( (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ){
				lexeme += ch;
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
			else{
				T = ID;
				break;
			}
		}
	}
	else{
		T = DONE;
	}
	return T;
}
