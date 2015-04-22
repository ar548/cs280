#include "p2lex.h"
#include "values.h"
#include <cstdlib>
#include <fstream>
#include <map>

using namespace Values;

// ...

// this is a global map used to keep values that are assigned to variables
// the key is the identifier
map<string,Value*> variables;
map<string, int> setIDs;
int errcnt = 0;
extern int currLine;

class PTree {
protected:
	PTree *left;
	PTree *right;

public:
	PTree(PTree *left = 0, PTree *right = 0) {
		this->left = left;
		this->right = right;
	}

	// ... other stuff ...
	//
	virtual Types getType() { return T_NONE; }

	virtual Value *eval() { return new Value(); }
};

class PTreeStmtList : public PTree {
public:
	PTreeStmtList(PTree *s1, PTree *s2 = 0) : PTree(s1, s2) {}

	Value *eval() {
		Value *v;
		if( left ) {
			v = left->eval();
			delete v;
		}
		if( right ) {
			v = right->eval();
			delete v;
		}
		return new Value();
	}
};

class PTreePrint : public PTree {
public:
	PTreePrint(PTree *expr) : PTree(expr) {}

	Value *eval() {
		Value *vprint = left->eval();
		cout << vprint << endl;
		delete vprint;
		return new Value();
	}
};

class PTreeSet : public PTree {
public:
	string id;
	PTreeSet(PTree *expr, string lex): PTree(expr) {
		this->id = lex;
	}

	Types getType(){
		Types t = left->getType();
		if(t == T_NONE){
			return T_NONE;
		}
		else if(t == T_STRING){
			return T_STRING;
		}
		else if(t == T_INT){
			return T_INT;
		}
		else{
			cerr << "WTF" << endl;
			return T_NONE;
		}
	}

	Value *eval(){
		Value *v;
		v = left->eval();
		
		if(v->getType() == T_NONE){
			cerr << "nonvalid expression" << endl;
		}
		else{
			variables[id] = v;
		}

		delete v;
		return new Value();
	}
};



class PTreePlus : public PTree {
public:
	PTreePlus(PTree *s1, PTree *s2 = 0) : PTree(s1, s2) {}

	// specification says:
	// int + int is int
	// string + string is string
	// anything else is an error
	Types getType() {
		Types ltype = left->getType();
		Types rtype = right->getType();

		if( ltype == T_NONE || rtype == T_NONE )
			return T_NONE;

		if( ltype == rtype )
			return ltype;

		return T_NONE;
	}

	Value *eval() {
		Value *l, *r;
		l = left->eval();
		r = right->eval();

		Value *answer;
		if( l->getType() == T_INT )
			answer = new ValueInt( l->getIValue() + r->getIValue() );
		else
			answer = new ValueString( l->getSValue() + r->getSValue() );
		delete l;
		delete r;
		return answer;
	}
};

class PTreeMinus : public PTree {
public:
	PTreeMinus(PTree *s1, PTree *s2 = 0) : PTree(s1, s2) {}
	
	// specification says:
	// int - int = int
	// string - string = string
	// anything else is an error
	Types getType(){
		Types ltype = left->getType();
		Types rtype = right->getType();

		if( ltype == T_NONE || rtype == T_NONE )
			return T_NONE;
		
		if( ltype == rtype )
			return ltype;
		
		return T_NONE;
	}

	Value *eval(){
		Value *l, *r;
		l = left->eval();
		r = right->eval();

		Value *ans;
		if( l->getType() == T_INT ){
			ans = new ValueInt( l->getIValue() - r->getIValue() );
		}
		else{
			string s1 = l->getSValue();
			string s2 = r->getSValue();
			int x = s1.find(s2);
			ans = new ValueString( s1.substr(0,x) + s1.substr(x+s2.length()) );
		}
		delete l;
		delete r;
		return ans;
	}
};

class PTreeStar : public PTree {
public:
	PTreeStar(PTree *s1, PTree *s2 = 0) : PTree(s1, s2) {}
	
	// specification says:
	// int * int = int
	// int * string = string
	// string * int = string
	// anything else is an error
	Types getType(){
		Types ltype = left->getType();
		Types rtype = right->getType();

		if( ltype == T_NONE || rtype == T_NONE )
			return T_NONE;

		if( ltype == T_INT && rtype == T_INT )
			return T_INT;
		else if( (ltype == T_INT && rtype == T_STRING) || (ltype == T_STRING && rtype == T_INT) )
			return T_STRING;
		else{
			cerr << "invalid multiplication" << endl;
			return T_NONE;
		}
	}

	Value *eval(){
		Value *l, *r;
		l = left->eval();
		r = right->eval();
		
		Value *ans;
		if ( l->getType() == T_INT && r->getType() == T_INT ){
			ans = new ValueInt(  l->getIValue() * r->getIValue() );
		}
		else if( l->getType() == T_INT && r->getType() == T_STRING ){
			int n = l->getIValue();
			string s1 = r->getSValue();
			string a = "";

			for(int i = 0; i<n; i++)
				a += s1;
			
			ans = new ValueString(a);
		}
		else if( l->getType() == T_INT && r->getType() == T_STRING ){
			int n = r->getIValue();
			string s1 = r->getSValue();
			string a = "";

			for(int i = 0; i<n; i++)
				a+= s1;

			ans = new ValueString(a);
		}
		delete l;
		delete r;
		return ans;
	
	}
};

class PTreeSlash : public PTree {
public:
	PTreeSlash(PTree *s1, PTree *s2 = 0) : PTree(s1, s2) {}
	
	// specification says:
	// int / int = int
	// string / int = string
	// int / string = string
	// all other combinations are errors
	Types getType(){
		Types ltype = left->getType();
		Types rtype = right->getType();
		
		if( ltype == T_NONE || rtype == T_NONE )
			return T_NONE;

		if( ltype == T_INT && rtype == T_INT )
			return T_INT;
		else if( (ltype == T_INT && rtype == T_STRING) || (ltype == T_STRING && rtype == T_INT) )
			return T_STRING;
		else{
			cerr << "invalid division" << endl;
			return T_NONE;
		}
	}

	Value *eval(){
		Value *l, *r;
		l = left->eval();
		r = right->eval();

		Value *ans;
		if ( l->getType() == T_INT && r->getType() == T_INT ){
			ans = new ValueInt( (int)(l->getIValue() / r->getIValue()) );
		}
		else if( l->getType() == T_INT && r->getType() == T_STRING ){
			int n = l->getIValue();
			string s = r->getSValue();
			ans = new ValueString( s.substr(s.length()-n) );
		}
		else if( l->getType() == T_STRING && r->getType() == T_INT ){
			int n = r->getIValue();
			string s = l->getSValue();
			ans = new ValueString( s.substr(0, s.length()-n) );
		}
		delete l;
		delete r;
		return ans;
	}
};

class PTreeID : public PTree {
	string id;
public:
	PTreeID(string id) : PTree() { this->id = id; }

	Types getType(){
		Value *v;
		v = variables[id];
		if( v->hasInt() ){
			return T_INT;
		}
		else if( v->hasStr() ){
			return T_STRING;
		}
		else return T_NONE;
	}

	Value *eval() {
		Value *value, *copy;

		value = variables[id];
		if( value->hasInt() )
			copy = new ValueInt( value->getIValue() );
		else
			copy = new ValueString( value->getSValue() );

		return copy;
	}
};

class PTreeINT : public PTree {
	ValueInt v;
public:
	PTreeINT(int val) : PTree() { v.setIValue(val); }
	Types getType() { return T_INT; }

	Value *eval() {
		return new ValueInt(v.getIValue());
	}
};

class PTreeSTRING : public PTree {
	ValueString v;
public:
	PTreeSTRING(string val) : PTree() { v.setSValue(val); }
	Types getType() { return T_STRING; }

	Value *eval() {
		return new ValueString(v.getSValue());
	}
};

extern PTree *Program(istream *br);
extern PTree *StmtList(istream *br);
extern PTree *Stmt(istream *br);
extern PTree *Expr(istream *br);
extern PTree *Term(istream *br);
extern PTree *Primary(istream *br);

PTree *Program(istream *br){
	return StmtList(br);
}

PTree *StmtList(istream *br){
	PTree *stmt;
	stmt = Stmt(br);

	if( stmt ){
		return new PTreeStmtList( stmt, StmtList(br) );
	}
	else {
		 return 0;
	}
}

PTree *Stmt(istream *br){
	string lex;
	Token T = getToken(br, lex);
	
	if( T == PRINT ){
		// the statement is a print statement
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
			return new PTreeSet( Expr(br), lex);
		}
	}
	else if( T == DONE )
		return 0;
	else{
		//cerr << currLine << ": not a valid statement" << endl;
		return 0;
	}
}

PTree *Expr(istream *br){
	PTree *term = Term(br);
	if( term == 0 ){
		return 0;
	}

	string lex;
	Token t = getToken(br, lex);
	if( t != PLUS && t != MINUS ){
		pushbackToken(t, lex);
		return term;
	}
	
	PTree *expr = Expr(br);
	if( expr == 0 ) {
		cerr << "Expected an expression" << endl;
		return 0;
	}
	
	if( t == PLUS )
		return new PTreePlus(term,expr);
	else if ( t == MINUS)
		return new PTreeMinus(term,expr);
	else{
		cerr << "this should never print" << endl;
		return 0;
	}
}

PTree *Term(istream *br){
	PTree *prmy = Primary(br);
	if( prmy == 0 ){
		return 0;
	}

	string lex;
	Token t = getToken(br, lex);
	if( t != STAR && t != SLASH ){
		pushbackToken(t, lex);
		return prmy;
	}
	
	PTree *term = Term(br);
	if( t == STAR )
		return new PTreeStar(prmy, term);
	else if( t == SLASH )
		return new PTreeSlash(prmy, term);
	else{
		cerr << "this should never print" << endl;
		return 0;
	}
}

PTree *Primary(istream *br){
	string lex;
	Token t = getToken(br, lex);
	
	if( t == ID ){
		if(setIDs[lex]){
			return new PTreeID(lex);
		}
		else {
			cerr << "Identifier " << lex << " is used without being set" << endl;
			return 0;
		}
	}
	else if( t == INT ){
		return new PTreeINT( atoi(lex.c_str()) );
	}
	else if( t == STRING){
		return new PTreeSTRING(lex);
	}
	else {
		cerr << currLine << ": invlaid primary" << endl;
		pushbackToken(t, lex);
		return 0;
	}
}

int main( int argc, char *argv[] ){
	istream *br;
	ifstream in;

	if (argc == 1){
		br = &cin;
	}
	else if(argc == 2){
		in.open(argv[1]);
		if(in.is_open()){
			br = &in;
		}
		else{
			cerr << "Error: cannot open " << argv[1] << endl;
			return 1;
		}
	}
	else {
		cerr << "Error: this program takes either no files or one filename as an argument" << endl;
		return 1;
	}
	
	if(debug){
		cout << "test" << endl;
		PTree *v1 = new PTreeINT(3);
		PTree *v2 = new PTreeSTRING("help");
		Value *a = v1->eval();
		Value *b = v2->eval();
		cout << a << ":" << b << endl;
		cout << "/test" << endl;
	}

	PTree *program;
	program = Program(br);
	if( !program || errcnt )
		return 0;
    
	// do all semantic checks... then...

	Value *val = program->eval();
	delete val;

	return 0;
}
