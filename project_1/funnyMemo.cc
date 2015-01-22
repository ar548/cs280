#include <iostream>
#include <cstdlib>

using namespace std;

int main (int argc, char *argv[]) {
	//argc is the number of cmd arguments argv is an array of the arguments
	//where argv[0] is the first going from left to right
	cout << "There were " << argc << " arguments on the command line" << endl;
	for( int i=0; i<argc; i++ ) {
		cout << i << ":" << argv[i] << ":" << endl;
	}
	
    return 0;
}
