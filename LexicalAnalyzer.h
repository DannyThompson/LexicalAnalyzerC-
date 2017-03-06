#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>
#include <iterator>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

enum token_type {LET_T = -35, STRINGP_T = -30, CHARP_T, NULLP_T, ZEROP_T, LISTP_T, SYMBOLP_T, NUMBERP_T,
		 QUOTE_T=-23,DEFINE_T,NOT_T,OR_T,AND_T,
		 WHILE_T,IF_T,CONS_T,LISTOP_T,IDENT_T,
		 NUMLIT_T,PLUS_T,MINUS_T,MULT_T,DIV_T,
		 LTE_T,GTE_T,LT_T,GT_T,EQUALTO_T,
		 RPAREN_T,LPAREN_T,NONE = -1, EOF_T, NUM_TOKENS, NEW_LINE};		



class LexicalAnalyzer 
{
    public:
	LexicalAnalyzer (char * filename);
	~LexicalAnalyzer ();
	token_type GetToken ();
	string GetTokenName (token_type t) const;
	string GetLexeme () const;
	void ReportError (const string & msg);
	std::map<int, token_type> dfaMap; //
	int getErrors(); //Function we added to return the number of errors.
	string getErrorReport();
	
 private:
	
	ifstream input; //Initial file
	ofstream listing; //List of all of the lexemes
	ofstream debug; //Debug file
	token_type token; //Enumerated value. Most recently recognized lexeme
	string line; //The string containing the input file. Received line by line.
	int linenum = 0; //The current row in the matrix
	int pos = 0; //The current column in the matrix
	
	int _isnum; //value used in the isnum function
	bool isLetter(char &a); //used to check if a char is an alpha
	int isnum(char &a); //checks if a char is a numeric
	int mustPeek(char a); //Additional function used to peek agead.
	string lexeme; 
	int errors = 0;
	string errorReport; //We didn't use this with the way that we reported our errors. 
	std::map<char, int> token_y; //A second map that stores all of the single possible values as keys, with their indexes in the DFA as the values
	bool peek; //Used with mustPeek to peek ahead.

	
	

};
	
#endif
