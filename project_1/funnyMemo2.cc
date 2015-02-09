#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

string toUppercase(string);
string toLowercase(string);

int main (int argc, char *argv[]) {

	//makes sure that there are the right number or args
	if(argc != 3){
		cerr << "This program takes exeactly 2 arguments:\n";
		cerr << "The first is the ajdective to be added, the second is the file name.\n";
		return 1;
	}

	istream *br;
	ifstream infile;

	string adj = argv[1];
	adj = toLowercase(adj);//sets the correct format no matter what the input is

	//opens the file then makes sure that it is actually open
	infile.open(argv[2]);
	if(infile.is_open()){
		br = &infile;
	}
	else{
		cerr << "Error: Could not open " << string(argv[2]);
		return 1;
	}

	//gets the correct version of a/an for the given adj
	string vowels = "AaEeIiOoUu";
	string an = "a";
	for(int i = 0; i < 10; i++){
		if(adj.at(0) == vowels.at(i)){
			an = "an";
		}
	}

	//basic declaration of needed variables
	string line;
	char ch;
	string word;
	bool wasArticle = false;
	bool didArticle = false;

	while(br->good()){
		getline(*br, line);//gets the individual line from the file
		word = "";
		//increments through each character in the line
		for(int i = 0; i < line.length(); i++){
			ch =  line.at(i);
			//is the character alphanumeric: if so store it to a string otherwise print it
			if( (ch>=48 && ch<=57) || (ch>=65 && ch<=90) || (ch>=97 && ch<=122) ){
				word += ch;
			}
			else{
				//was the previous word an article
				if( wasArticle ){
					//matches the three case cases
					if(word == toUppercase(word) && word != ""){
						cout << toUppercase(adj);
					}
						else if (word == toLowercase(word)){
						cout << toLowercase(adj);
					}
					else if( word.at(0) == toupper(word.at(0)) ){
						adj[0] = toupper(adj[0]);
						cout << adj;
						toLowercase(adj);
					}
					else{
						cout << adj;
					}
					cout << ' ' + word + ch;
					wasArticle = false;
					didArticle = true;//used to handle the "a a day" case
				}
				//checks if the word is the. ignored if the previous word was an article making this one a noun
				else if( toLowercase(word) == "the" && !didArticle ){
					wasArticle = true;
					cout << word + ch;
				}
				//checks if the word is a. ignored if the previous word was an article making this one a noun
				else if( (toLowercase(word) == "a" || toLowercase(word) == "an") && !didArticle ){
					wasArticle = true;
					//gets the correct capitalization for the word A / An
					if(word.at(0) == 'A'){
						an[0] = toupper(an[0]);
					}
					cout << an + ch;
					an = toLowercase(an);
				}
				//failing all the other print out the word
				else{
					cout << word << ch;
					didArticle = false;
				}
				word = "";
			}
		}
		//handles the word at the end of the line.  this was done bacause i could not read the whole file in character by
		//character
		if(toLowercase(word) == "the" && !didArticle ){
			wasArticle = true;
			cout << word + '\n';
		}
		else if( (toLowercase(word) == "a" || toLowercase(word) == "an") && !didArticle ){
			wasArticle = true;
			if(word.at(0) == 'A'){
				an[0] = toupper(an[0]);
			}
			cout << an + '\n';
			an = toLowercase(an);
		}
		else{
			didArticle = false;
			cout << word << '\n';
		}
	}

return 0;
}

//simple comversion helper functions: self explanitory
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
