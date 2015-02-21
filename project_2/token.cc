#include "p2lex.h"
#include <fstream>
#include <iostream>

Token getToken(istream *br, string &lexeme){
	lexeme = "";
	char ch;
	string word;
	while(br->good()){
		ch = br->get();
		if( (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ){
			//TODO put some logical logic here
			lexeme += ch;
		}
		else if(ch == '+'){
			return PLUS;
		}
		else if(ch == '-'){
			return MINUS;
		}
		else if(ch == '*'){
			return STAR;
		}
		else if(ch == '/'){
			return SLASH;
		}
		else if(ch == ';'){
			return SC;
		}
		else{
			if(lexeme == "set"){
				cout << "set" << endl;
			}
			else if (lexeme == "print"){
				cout << "print" << endl;
			}
			else{
				lexeme = word;
				return ID;
			}
		}
	}
	Token t = DONE;
};
