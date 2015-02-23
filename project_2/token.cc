#include "p2lex.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

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
					// this statement is needed because both SLASH and a comment start with a
					// '/'
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
				lexeme += ch;
				ch = br->get();
				lexeme += ch;
				while(ch != '"'){
					ch = br->get();
					if (ch == '\n'){
						//handles the possibility of an incomplete string
						T = DONE;
						return T;
					}
					lexeme += ch;
				}
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
