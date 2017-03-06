#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	lex = new LexicalAnalyzer (filename);
	token_type t;
	while ((t = lex->GetToken()) != EOF_T)
	{
	  if(lex->GetTokenName(t) == "Error")
	    lex->ReportError(lex->GetTokenName(t));
	  
	  else
	    cout << lex->GetTokenName(t) << "      " << lex->GetLexeme() << endl;
	  
	  
	  /*	  streambuf *psbuf, *backup;
	  ofstream filestr;
	  filestr.open ("l.ss");

	  backup = cout.rdbuf();     // back up cout's streambuf

	  psbuf = filestr.rdbuf();        // get file's streambuf
	  cout.rdbuf(psbuf); 


	  cout.rdbuf(backup);        // restore cout's original streambuf

	  filestr.close();*/

	  
		// get a token
		// write its name to the debug file
		// write the corresponding lexeme to the debug file
	}
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}
