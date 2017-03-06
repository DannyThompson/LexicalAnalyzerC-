#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{

  //Make an instance of Lexical analyzer and give it the file name
  lex = new LexicalAnalyzer (filename);
  token_type t; //Instance of the enumerated token type.
  
  //Make a string that will eventually be the output files name. Erase the input files end chars (.ss, etc.)
  string s = filename;
  s = s.substr(0, s.size() - 3);
  


  while ((t = lex->GetToken()) != EOF_T)
    {
      //Ofstreams for each of the tiles we want to out put to.
      ofstream out;
      ofstream out2;
      ofstream out3;
      out.open(s + ".p1", ios_base::app);
      out2.open(s + ".dbg", ios_base::app);
      out3.open(s + ".lst", ios_base::app);
       
     
      out << lex->GetTokenName(t) << "      " << lex->GetLexeme() << endl;      
      
      //If an error is found, add it to the .dbg file.
      if(t == (token_type) -500){
	out2 << lex->getErrorReport() << endl;      
      }

      //Add everything to the .lst file.
      out3 << lex->GetTokenName(t) << "      " << lex->GetLexeme() << endl;
      if(t == (token_type) - 500){
	out3 << lex->getErrorReport() << endl;      
      }
    }
    ofstream errors; //This is used to append the errors to the very end of the dbg file.
    errors.open(s + ".dbg", ios_base::app);
    errors << "Total errors in file: " << lex->getErrors();

}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}


