
#include "LexicalAnalyzer.h"
#include "Dfa.hpp"


using namespace std;

static string token_names[] = {	"EOF_T" }; 


LexicalAnalyzer::LexicalAnalyzer (char * filename)
{

  /*
   * Cumbersome map. Inverse of the token_y map.
   * This helps us get to the right column in our dfa matrix.
   */
  map1[-23] = QUOTE_T, map1[-22] = DEFINE_T, map1[-21] = NOT_T,
    map1[-20] = OR_T, map1[-19] = AND_T, map1[-18] = WHILE_T,
    map1[-17] = IF_T, map1[-16] = CONS_T, map1[-2] = LPAREN_T,
    map1[-3] = RPAREN_T, map1[-8] = LTE_T, map1[-6] = GTE_T,
    map1[-7] = LT_T, map1[-5] = GT_T, map1[-4] = EQUALTO_T,
    map1[-10] = MULT_T, map1[-9] = DIV_T, map1[-11] = MINUS_T,
    map1[-12] = PLUS_T, map1[-13] = NUMLIT_T, map1[-14] = IDENT_T,
    map1[-15] = LISTOP_T, map1[-30] = STRINGP_T, map1[-29] = CHARP_T,
    map1[-28] = NULLP_T, map1[-27] = ZEROP_T, map1[-26] = LISTP_T,
    map1[-25] = SYMBOLP_T, map1[-24] = NUMBERP_T;


  /*
   * Second map. Inverse of the above so we can go back and forth 
   * between the enum key and val pairs.
   */
  
  token_y['\''] = 0,
    token_y['('] = 1,
    token_y[')'] = 2,
    token_y['>'] = 3,
    token_y['='] = 4,
    token_y['<'] = 5,
    token_y['/'] = 6,
    token_y['*'] = 7, 
    token_y['-'] = 8,
    token_y['+'] = 9,
    token_y['#'] = 10, 
    token_y[' '] = 11,
    token_y['.'] = 12,
    token_y['?'] = 13, 
    token_y['_'] = 14,
    token_y['A'] = 15, 
    token_y['c'] = 16,
    token_y['o'] = 17,
    token_y['n'] = 18,
    token_y['s'] = 19,
    token_y['i'] = 20,
    token_y['f'] = 21,
    token_y['w'] = 22,
    token_y['h'] = 23,
    token_y['l'] = 24,
    token_y['e'] = 25,
    token_y['a'] = 26,
    token_y['d'] = 27,
    token_y['r'] = 28,
    token_y['t'] = 29;
  

  input.open(filename);

  //Check if the input file is valid. If not print an error.
  if(!input){
    cout << "Error opening file. Try again" << endl;
    system("pause");
  }
  
  //Get the input file line by line into the 'line' string
  stringstream s;
  getline(input, line);
  s << line;
  while(!input.eof()){
    getline(input,line);
    s << line;
  }
  line = s.str();
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
  input.close();
}

token_type LexicalAnalyzer::GetToken()
{
	char c;
	peak = false;

	int state=0;
	lexeme = "";

	if(!line.empty()){
	  
	  c = line[0];
	  lexeme += c;
	  line.erase(line.begin());
	  
	  /*  //Check for unrecognized symbols
	  if(token_y.find(c) == token_y.end())
	  return (token_type) -500;*/
	  
	  bool n = isnum(c);
	  bool alpha = isLetter(c);
	  peak = mustPeak(c);
	  state = dfa[state][token_y[c]];
	  
	  
	  
	  
	  
	  while (state > 0 & !line.empty()) {

	    //Check for unrecognized symbols
	    state -= 2;
	    int check = dfa[state][token_y['\'']];
	    char next = line[0];
	    //	    n = isnum(next);
	    //	    alpha = isLetter(next);
	    
	    if (peak == false) {
	      state = dfa[state][token_y[next]];
	    }
	    
	    //dont consume and break
	    if ((check == state && (peak == false) ) && state<0){
	      break;
	    }
	    	    
	    
	    c = line[0];
	    lexeme += c;
	    alpha = isLetter(c);
	    n = isnum(c);
	    line.erase(line.begin());

	    
	    if (peak == true) {
	      state = dfa[state][token_y[c]];   
	    }
	    
	  }
	}
	
	token = map1[state];
	return token;
	
	//If there isn't a map endstate on the first line of the DFA, we want to jump to the line of the positive number we encounter
}



string LexicalAnalyzer::GetTokenName (token_type t) const
{
  // The GetTokenName function returns a string containing the name of the
  // token passed to it. 


  //Placeholder string for the lexeme
  string l;
  
  //Switch statement for all of the possible lexemes in the Map
  switch (t)
    {
    case QUOTE_T:
      l = "QUOTE_T";
      break;
    case DEFINE_T:
      l = "DEFINE_T";
      break;
    case NOT_T:
      l = "NOT_T";
      break;
    case OR_T:
      l ="OR_T";
      break;
    case AND_T:
      l = "AND_T";
      break;
    case WHILE_T:
      l = "WHILE_T";
      break;
    case IF_T:
      l = "IF_T";
      break;
    case CONS_T:
      l = "CONS_T";
      break;
    case LISTOP_T:
      l = "LISTOP_T";
      break;
    case IDENT_T:
      l = "IDENT_T";
      break;
    case NUMLIT_T:
      l = "NUMLIT_T";
      break;
    case PLUS_T:
      l = "PLUS_T";
      break;
    case MINUS_T:
      l = "MINUS_T";
      break;
    case MULT_T:
      l = "MULT_T";
      break;
    case DIV_T:
      l = "DIV_T";
      break;
    case LTE_T:
      l = "LTE_T";
      break;
    case GTE_T:
      l = "GTE_T";
      break;
    case LT_T:
      l = "LT_T";
      break;
    case GT_T:
      l = "GT_T";
      break;
    case EQUALTO_T:
      l = "EQUALTO_T";
      break;
    case RPAREN_T:
      l = "RPAREN_T";
      break;
    case LPAREN_T:
      l = "LPAREN_T";
      break;
    case NONE:
      break;
    case EOF_T:
      break;
    case NUM_TOKENS:
      break;
    case (token_type) -500:
      //      l = GetLexeme();
      // return "Error, unrecognized token: " << l;
      break;
      
    default:
      return "ELSE";
      break;
    }
 
  return l;
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the get_token function
	return lexeme;
}

void LexicalAnalyzer::ReportError (const string & msg)
{

  errors +=1;
	
	
}

bool LexicalAnalyzer::isLetter(char &a){

  if(isalpha(a)){
    a = 'A';
    //    cout << a;
    return true;
  }
  
  /*
  if(token_y.find(a)->second > 15 && isalpha(a)){
    a = token_y.find(a)->first;
    cout << a;
    return false;
    }*/
  
  return false;
}

bool LexicalAnalyzer::isnum(char &a) {

  if (isdigit(a) ) {
    a = '#';
    return true;
  }
  return false;
}

bool LexicalAnalyzer::mustPeak(char a) {

	if (peak == false) {
		switch (a)
		{
		case'-':
		case'+':
		  //		case'A':
		  return true;


		default:
			return false;
		}
	}
	else
		return false;

}
