#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

int main (int argc, char *argv[]) {
	istream *br;
	ifstream infile;

	if(argc != 3){
		cerr << "This program takes exeactly 2 arguments:\n";
		cerr << "The first is the ajdective to be added, the second is the file name.\n";
		return 0;
	}

	string adj = argv[1];
	string vowels = "AaEeIiOoUu";
	string an = "a";
	for(int i = 0; i < 10; i++){
		if(adj.at(0) == vowels.at(i)){
			an = "an";
		}
	}
	infile.open(argv[2]);
	if(!infile.is_open()){
		cerr << "Error: Could not open" << string(argv[2]) << endl;
		return 1;
	}
	
	//in ascii 48-57 are numbers, 65-90 are capital, 97-122 are lowercase
	string line;
	char ch;
	string word;
	do{
		getline(*br, line);
		
		for(int i = 0; i < line.length(); i++ ){
			ch = line.at(i);
			if( (ch>=48 && ch<=57) || (ch>=65 && ch<=90) || (ch>=97 && ch<=122) ){
				word = word + ch;
			}
			else{
				cout << word << ch;
				word = "";
			}
		}
		cout << "\n";
	
	}while(br->good());

    return 0;
}
