//
//  skel4.cpp
//  skeleton for assignment 4
//

#include "p2lex.h"
#include "values.h"
#include <fstream>
#include <map>

using namespace Values;

// ...

// this is a global map used to keep values that are assigned to variables
// the key is the identifier
map<string,Value*> variables;

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
	PTreeSet(PTree *expr, string lex): PTree(expr) {}

	Value *eval() {
	
	}
}

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

// ....

class PTreeID : public PTree {
	string id;
public:
	PTreeID(string id) : PTree() { this->id = id; }

	// ...

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

class PTreeSTR : public PTree {
	ValueString v;
public:
	PTreeSTR(string val) : PTree() { v.setSValue(val); }
	Types getType() { return T_STRING; }

	Value *eval() {
		return new ValueString(v.getSValue());
	}
};

// ... parser ...

int
main( int argc, char *argv[] )
{
    // ... initial stuff
    
cout << "test" << endl;
	PTree *v1 = new PTreeINT(3);
	PTree *v2 = new PTreeSTR("help");
	Value *a = v1->eval();
	Value *b = v2->eval();
	cout << a << ":" << b << endl;
cout << "/test" << endl;

    PTree *program;

    program = Program(br);

    if( !program || errcnt )
    	return 0;
    
    // do all semantic checks... then...

    Value *val = program->eval();
    delete val;

    return 0;
}
