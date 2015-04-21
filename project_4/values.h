#ifndef VALUES_H
#define VALUES_H

#include <iostream>
#include <string>
using namespace std;

namespace Values {

enum Types {
	T_INT,		// for integer values
	T_STRING,	// for string values
	T_NONE,		// no type: an error
};

class Value {
public:
	virtual Types getType() { return T_NONE; }

	bool hasInt() { return getType() == T_INT; }
	bool hasStr() { return getType() == T_STRING; }

	virtual int getIValue() {
		cerr << "trying to get an int from something that isn't!\n";
		//exit(1);
	}
	virtual string getSValue() {
		cerr << "trying to get a string from something that isn't!\n";
		//exit(1);
	}

	virtual void setIValue(int v) {
		cerr << "trying to set an int for something that isn't!\n";
		//exit(1);
	}
	virtual void setSValue(string s) {
		cerr << "trying to set a string for something that isn't!\n";
		//exit(1);
	}

	// this is the way you allow a type that you create to be printed by ostream
	// NOTE i used a Value*, not a Value, because I have virtual functions in Value
	//    and I want to access them by following the pointer
	friend ostream& operator<< (ostream& out, Value* v) {
		if( !v )
			out << "<null>";
		else if( v->hasInt() )
			out << v->getIValue();
		else if( v->hasStr() )
			out << v->getSValue();
		else
			out << "<NONE>";
		return out;
	}
};

class ValueInt : public Value {
	int	theValue;

public:
	ValueInt(int v = 0) : theValue(v) {}
	Types getType() { return T_INT; }

	int getIValue() { return theValue; }
	void setIValue(int v) { theValue = v; }
};

class ValueString : public Value {
	string	theValue;

public:
	ValueString(string v = "") : theValue(v) {}
	Types getType() { return T_STRING; }
	string getSValue() { return theValue; }
	void setSValue(string s) { theValue = s; }
};

} // end namespace
#endif
