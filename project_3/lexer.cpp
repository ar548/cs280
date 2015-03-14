#include "p3lex.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Token getToken(istream *br, string &lexeme){
	Token T;
	lexeme = "";
	char ch;
	if(br->good()){
		while(br->good()){	
			// This loop is unneeded for the most part because the code inside
			// should only run if there is a comment.  It can be replaced with a 
			// GoTo statement however for this case the while loop is more efficent
			ch = br->get();
			if(ch == '+'){
				return PLUS;
			}
			else if(ch == '-'){
				return MINUS;
			}
			else if(ch == '*'){
				return STAR;
			}
			else if(ch == '/'){
				if(br->peek() == '/'){
					// this statement is needed because both SLASH 
					// and a comment start with a '/'
					do{
						ch = br->get();
					}while(ch != '\n');
					continue;	// This makes the outer while loop function as a 
				}
				else{
					return SLASH;
				}
			}
			else if(ch == ';'){
				return SC;
			}
			else if(ch == '"'){
				lexeme += ch;
				ch = br->get();
				lexeme += ch;
				while(ch != '"'){
					ch = br->get();
					if (ch == '\n'){
						//handles the possibility of an incomplete string
						return DONE;
					}
					else{
						lexeme += ch;
					}
				}
				return STRING;
			}
			else if( (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ){
				// This section handles all of the IDs and treats SET and PRINT as special
				// cases of IDs (a.k.a. reserved words)
				// It could also be made to handle strings but that was put elsewhere
				// for the sake of readibility
				lexeme += ch;
				while( (br->peek() >= 'A' && br->peek() <= 'Z') || (br->peek() >= 'a' && br->peek() <= 'z') ){
					ch = br->get();
					lexeme += ch;
				}
				if(lexeme == "set"){
					return SET;
				}
				else if(lexeme == "print"){
					return PRINT;
				}
				else{
					return ID;
				}
			}
			else if( (ch >= '0' && ch <= '9') ){
				// This block handles INTs of any length (eg. not just 32 bit ints).
				lexeme += ch;
				while(br->peek() >= '0' && br->peek() <= '9'){
					ch = br->get();
					lexeme += ch;
				}
				return INT;
			}
			else if( (ch == ' ' || ch == '\n' || ch == '\t') ){
				continue;
			}
			else{
				return DONE;
			}
		}
	}
	else{
		return DONE;
	}
}
