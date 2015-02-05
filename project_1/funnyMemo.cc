#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

string toUppercase(string);
string toLowercase(string);

int main (int argc, char *argv[]) {
	istream *br;
	ifstream infile;
	
	if(argc != 3){
		cerr << "This program takes exeactly 2 arguments:\n";
		cerr << "The first is the ajdective to be added, the second is the file name.\n";
		return 0;
	}
	
	string adj = argv[1];
	adj = toLowercase(adj);
	adj[0] = toupper(adj[0]);//sets the correct case
	
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

	//in ascii 48-57 are numbers, 65-90 are capital, 97-122 are lowercase
	//add the adj to the word after the article using a boolean

	string line;
	char ch;
	string word;
	bool wasArticle = false;
	
	do{
		getline(*br, line);
		word = "";
		for(int i = 0; i < line.length(); i++ ){
			ch = line.at(i);
			if( (ch>=48 && ch<=57) || (ch>=65 && ch<=90) || (ch>=97 && ch<=122) ){
				word = word + ch;
			}
			else{
				//cout << word << ch;
				if(wasArticle){
					if(word == toUppercase(word)){
						cout << toUppercase(adj);
					}
					else if(word == toLowercase(word)){
						cout << toLowercase(adj);
					}
					else{
						cout << word;
					}
					cout << " " << word << ch;
					wasArticle = false;
				}
				else if ( word == "the" || word == "The" || word == "tHe" || word == "THe" || word == "thE" || word == "ThE" || word == "tHE" || word == "THE" ){
					cout << word << ch;
					wasArticle = true;
						
					
				}
				else if(word == "a" || word == "A" || word == "an" || word == "An" || word == "aN" || word == "AN"){
					if(word.at(0) == 'A'){
						an[0] = toupper(an[0]);
					}
					cout << an << ch;
					wasArticle = true;

				}
				else{
					cout << word << ch;
				}
				word = "";
			}
		}
		cout << word << "\n";
	
	}while(br->good());

    return 0;
}

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
