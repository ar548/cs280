#include "p2lex.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

// global variables for the file
map<string, int> setIDs;
extern int currLine;
int numLeaves = 0;

// class definitions ->
	// : PTree
	// : PTreeStmtList
	// : PTreeSet 
	// : PTreePrint 
	// : PTreeExpr 
	// : PTreeTerm 
	// : PTreeID 
	// : PTreeSTRING 
	// : PTreeINT

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
	PTreeSet( string str, PTree *s2 ) : PTree(0, s2){
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
	PTreeExpr(char c, PTree *s1, PTree *s2 = 0) : PTree(s1, s2) {
		op = c;
	};

	char op;

};

class PTreeTerm : public PTree {
public:
	PTreeTerm(char c, PTree *s1, PTree *s2 = 0) : PTree(s1, s2) {
		op = c;
	};

	char op;
};

class PTreeID : public PTree {
public:
	PTreeID(string& str) : PTree(0, 0) {
		name = str;
	}
	string name;
	int valInt;
	string valString;
};

class PTreeSTRING : public PTree {
public:
	PTreeSTRING(string& str) : PTree(0, 0) {
		val = str;
	}
	string val;
};

class PTreeINT : public PTree {
public:
	PTreeINT(string str) : PTree(0, 0) {
		val = str;
	}
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
			pushbackToken(T2, lex);
			return 0;
		}
		else{
			setIDs[lex] = 1;
			//pushbackToken(T2, lex);
			return new PTreeSet( lex, Expr(br) ); 
		}	
	}
	else if( T == DONE ){
		return 0;
	}
	else{
		cerr << currLine << ": not a valid statement" << endl;
		return 0;
	}
}

// Expr ::= Expr PLUS Term | Expr MINUS Term | Term
PTree *Expr(istream *br){
	string lex;

	PTree *term = Term(br);
	Token t = getToken(br, lex);
	if(t == SC){
		return new PTreeExpr(NULL, term, 0);
	}
	else if(t == PLUS){
		PTree *exp = Expr(br);
		return new PTreeExpr('+', term, exp);	// this may have to get an extra parameter for a plus sign
	}
	else if(t == MINUS){
		PTree *exp = Expr(br);
		return new PTreeExpr('-', term, exp);	// this may have to get an extra parameter for the minus sign
	}
	else if(t == SET || t == PRINT){
		cerr << currLine << ": Missing semicolon" << endl;
		pushbackToken(t, lex);
	}
	else{
		return 0;
	}
}

// Term ::= Term PLUS Primary | Term MINUS Primary | Primary
PTree *Term(istream *br){
	string lex;

	PTree *prmy = Primary(br);
	Token t = getToken(br, lex);
	if(t == SC || t == PLUS || t == MINUS){
		pushbackToken(t, lex);
		return new PTreeTerm(NULL, prmy, 0);
	}
	else if(t == STAR){
		PTree *term = Term(br);
		return new PTreeTerm('*', prmy, term);
	}
	else if(t == SLASH){
		PTree *term = Term(br);
		return new PTreeTerm('/', prmy, term);
	}
	else if( t == SET || t == PRINT ){
		pushbackToken(t, lex);
		return new PTreeTerm(NULL, prmy, 0);
	}
	else{
		pushbackToken(t, lex);
		return 0;
	}
}

// Primary ::= STRING | INT | ID
PTree *Primary(istream *br){
	string lex;
	Token T = getToken(br, lex);
	numLeaves++;
	if( T == ID ){
		if(setIDs[lex]){
			return new PTreeID(lex);
		}
		else{
			cerr << "Identifier " << lex << " is used without being set" << endl;
			//exit(1);
			return 0;
		}
	}
	else if( T == INT ){
		return new PTreeINT(lex);
	}
	else if( T == STRING ){
		return new PTreeSTRING(lex);
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
	if( !(prg) && (numLeaves != 0) ){
		cout << "There were " << numLeaves << " leaves in the parse tree." << endl;
	}
}
