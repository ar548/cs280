#include "p2lex.h"
#include <fstream>
#include <iostream>

Token getToken(istream *br, string &lexeme){
	lexeme = "";
	char ch;
	while(br->good()){
		ch = br->get();
		if( (ch >= A && ch <= Z) || (ch >= a && ch <= z) ){
			//TODO put some logical logic here
			lexeme += ch;
		}
		else if(ch == '+'){}
		else if(ch == '-'){}
		else if(ch == '*'){}
		else if(ch == '/'){}
		else if(ch == ';'){}
		else{
			if(lexeme == "set"){
				cout << "set" << endl;
			}
			else if (lexeme == "print"){
				cout << "print" << endl;
			}
			else{}
		}
	}
};
