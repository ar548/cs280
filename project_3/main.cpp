#include "p2lex.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

// global variables for the file
map<string, int> setIDs;
extern int currLine;


class PTree {
	PTree *left;
	PTree *right;

public:
	PTree(PTree *left, PTree *right = 0) {
		this->left = left;
		this->right = right;
	}
};

class PTreeStmtList : public PTree {
public:
	PTreeStmtList(PTree *s1, PTree *s2 = 0) : PTree(s1, s2) {};
};

class PTreeSet : public PTree {
public:
	PTreeSet(string& str, PTree *s1/*, PTree *s2 = 0/**/) : PTree(s1/*, s2*/) {
		idToSet = str;
	};
	string idToSet;
};

class PTreePrint : public PTree {
public:
	PTreePrint(PTree *s) : PTree(s, 0) {};
};

class PTreeExpr : public PTree {
public:
	PTreeExpr(PTree *s1, PTree *s2 = 0) : PTree(s1, s2) {};
};

class PTreeTerm : public PTree {
public:
	PTreeTerm(PTree *s1, PTree *s2 = 0) : PTree(s1, s2) {};
};

class PTreeID : public PTree {
public:
	PTreeID(string& str) : PTree(0, 0) {
		//this->left = 0;
		//this->right = 0;
		name = str;
	}
//private:		//this is only commented out for debugging purposes
	string name;
	int valInt;
	string valString;
};

class PTreeSTRING : public PTree {
public:
	PTreeSTRING(string& str) : PTree(0, 0) {
		//this->left = 0;
		//this->right = 0;
		val = str;
	}
//private: 		//this is only commented out for debugging purposes
	string val;
};

class PTreeINT : public PTree {
public:
	PTreeINT(string str) : PTree(0, 0) {
        	//this->left = 0;
		//this->right = 0;
		val = str;
	}
//private: 		// this is only commented out for debugging purposes

	string val;	// TODO this needs to be changed to an int and I need to find a 
			// 	a function to do that or write my own
};

extern PTree *Program(istream *br);
extern PTree *StmtList(istream *br);
extern PTree *Stmt(istream *br);
extern PTree *Expr(istream *br);
extern PTree *Term(istream *br);
extern PTree *Primary(istream *br);

// Program ::= StmtList
PTree *Program(istream *br){
	return StmtList(br);
}

// StmtList ::= Stmt | Stmt StmtList
PTree *StmtList(istream *br){
	PTree *stmt;

	stmt = Stmt(br);

	if( stmt ){
		return new PTreeStmtList( stmt, StmtList(br) );
	}
	else{
		return 0;
	}
}

// Stmt ::= PRINT Expr SC | SET ID Expr SC
PTree *Stmt(istream *br){
	string lex;

	Token T = getToken(br, lex);
	if( T == PRINT ){
		// the statement a PRINT statement
		return new PTreePrint( Expr(br) );	
	}
	else if( T == SET ){
		// the statement a SET statement
		Token T2 = getToken(br, lex);
		if( T2 != ID ){
			cerr << "Error : invalid set statement at line " << currLine  << "." << endl;
			cerr << "\tA set statement must follow the pattern \"SET ID Expr;\"" << endl;
			return 0;
		}
		else{
			setIDs[lex] = 1;
			return new PTreeSet( lex, Expr(br) );	// TODO this line needs to be fixed 
								// 	ask the prof how to make just 
								// 	the ID a PTree leaf
		}	
	}
	else{
		cerr << "Error : invalid statement at line " << currLine  << "." << endl;
		cerr << "\tA valid statement is either \"PRINT Expr;\" or \"SET ID Expr;\"" << endl;
		// TODO ask the prof what needs to be done in the case of a non conforming statement
		return 0;
	}
}

// Expr ::= Expr PLUS Term | Expr MINUS Term | Term
PTree *Expr(istream *br){
	string lex;
	Token T1 = getToken(br, lex);
	
	PTree *term = Term(br);
	PTree *exp = Expr(br);
	
	if( term ){
		return new PTreeExpr(term, exp);
	}
	else{
		cerr << "Error : invalid expression at line " << currLine << "." << endl;
		cerr << "\tA valid expression \"Term\" or \"Term {+|-} Expr\"" << endl;
		return 0;
	}
}

PTree *Term(istream *br){
	return 0;
}

PTree *Primary(istream *br){
	string lex;
	Token T = getToken(br, lex);
	
	if( T == ID ){

	}
	else if( T == INT ){

	}
	else if( T == STRING ){

	}
	else{
		return 0;
	}
}

int main(int argc, char *argv[]){
	istream *br;
	ifstream infile;
	string lex;
				
	if(argc == 2){
		// gets the input from a file
		infile.open( argv[1] );
		if( infile.is_open() ){
			br = &infile;
		}
		else{
			cerr << "Error: Could not open " << string(argv[1]) << endl;
			return 1;
		}
	}
	else if( argc == 1 ){
		// gets standard user input
		br = &cin;
	}
	else{
		cerr << "Error: Too many args" << endl;
		cerr << "This program takes either no args and reads standard user input or\n";
		cerr << "It can take 1 arg which is the name of a file it will read\n";
		return 1;
	}

	PTree *prg = Program(br);
}
