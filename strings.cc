#include<string>
#include<iostream>

using namespace std;

// a string in C is a string of characters with a NULL characters at the end
// this is simmilar to an array of characters

int main (){
	string mystring = "hello!";
	string yourstring = mystring;

	cout << mystring.length() << endl;
	cout << mystring.at(3) << endl;
	cout << mystring[] << endl;

    return 0;
}
