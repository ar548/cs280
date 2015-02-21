#include "p2lex.h"
#include<iostream>
#include<string>
#include<fstream>

Token getToken(istream *br, string& lexeme){
	Token T;
	lexeme = "";
	char ch;
	if(br->good()){
		while(br->good()){
			if( (ch >= 'A'&& ch <= 'Z') || (ch >= 'a' && ch <= 'z') ){
				lexeme += ch;
			}
			else{
				return ID;
			}
		}
	}
	else {
		return DONE;
	}
	return T;
}
