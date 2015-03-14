#include "p3lex.h"
#include <vector>

class program{
private:
	stmtlist s();
public:
	program(istream *br, string& lexeme);

};

class stmtlist{
private:
	vector<stmt> stmts;
public:

};

class stmt{

};

class print : public stmt{

};

class set : public stmt{

};

class expr{

};

class term{

};

class primary{

};




/*
class expr{
private:
	enum{
		int_p_int;	// int + int
		int_m_int;	// int - int
		int_t_int;	// int * int
		int_d_int;	// int / int

		str_p_str;	// string + string
		str_m_str;	// string - string

		str_t_int;	// string * int
		int_t_str;	// int * string
		str_d_int;	// string / int
		int_d_str;	// int / string
	}
	expr *exp;
	term

};
/**/
