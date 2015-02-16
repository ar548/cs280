#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

string toUppercase(string);
string toLowercase(string);

int main (int argc, char *argv[]) {

	if(argc != 3){
		cerr << "This program takes exeactly 2 arguments:\n";
		cerr << "The first is the ajdective to be added, the second is the file name.\n";
		return 1;
	}

	istream *br;
	ifstream infile;

	string adj = argv[1];
	adj = toLowercase(adj);

	infile.open(argv[2]);
	if(infile.is_open()){
		br = &infile;
	}
	else{
		cerr << "Error: Could not open " << string(argv[2]);
		return 1; 
	}

	string vowels = "AaEeIiOoUu";
	string an = "a";
	for(int i = 0; i < 10; i++){
		if(adj.at(0) == vowels.at(i)){
			an = "an";
		}
	}
	
	string line;
	string text;
	char ch;
	string word;
	bool wasArticle = false;
	bool didArticle = false;
	
	// stores the entire file to a single string
	while( br->good()){
		getline(*br, line);
		if( br->good() )
			text = text + line + '\n';
	}
	
	// itterates through the string getting one word at a time
	for(int i = 0; i < text.length(); i++){
		ch = text.at(i);
		if( (ch>=48 && ch<=57) || (ch>=65 && ch<=90) || (ch>=97 && ch<=122) ){
			word += ch;
		}
		else{
			if( wasArticle && word != "" ){
				if(word == toUppercase(word) && word != ""){
					cout << toUppercase(adj);
				}
				else if( word == toLowercase(word) ){
					cout << toLowercase(adj);
				}
				else if( word.at(0) == toupper(word.at(0)) ){
					adj[0] = toupper(adj[0]);
					cout << adj;
					adj = toLowercase(adj);
				}
				else{
					cout << adj;
				}
				cout << ' ' + word + ch;
				wasArticle = false;
				//didArticle = true;
			}
			else if( toLowercase(word) == "the" && !didArticle ){
				wasArticle = true;
				cout << word + ch;
			}
			else if( (toLowercase(word) == "a" || toLowercase(word) == "an") && !didArticle ){
				wasArticle = true;
				if(word.at(0) == 'A'){
					an[0] = toupper(an[0]);
				}
				cout << an + ch;
				an = toLowercase(an);
			}
			else{
				cout << word + ch;
				didArticle = false;
			}
			word = "";
		}
	}	
	return 0;
}

//simple conversion helper function: self-explanitory
string toUppercase(string s){
	string str = "";
	for(int i = 0; i < s.length(); i++){
		str += toupper(s[i]);
	}
	return str;
}

string toLowercase(string s){
	string str;
	for(int i = 0; i < s.length(); i++){
		str += tolower(s[i]);
	}
	return str;
}
