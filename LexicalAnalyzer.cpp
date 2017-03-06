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
  dfaMap[-23] = QUOTE_T, dfaMap[-22] = DEFINE_T, dfaMap[-21] = NOT_T,
    dfaMap[-20] = OR_T, dfaMap[-19] = AND_T, dfaMap[-18] = WHILE_T,
    dfaMap[-17] = IF_T, dfaMap[-16] = CONS_T, dfaMap[-2] = LPAREN_T,
    dfaMap[-3] = RPAREN_T, dfaMap[-8] = LTE_T, dfaMap[-6] = GTE_T,
    dfaMap[-7] = LT_T, dfaMap[-5] = GT_T, dfaMap[-4] = EQUALTO_T,
    dfaMap[-10] = MULT_T, dfaMap[-9] = DIV_T, dfaMap[-11] = MINUS_T,
    dfaMap[-12] = PLUS_T, dfaMap[-13] = NUMLIT_T, dfaMap[-14] = IDENT_T,
    dfaMap[-15] = LISTOP_T, dfaMap[-30] = STRINGP_T, dfaMap[-29] = CHARP_T,
    dfaMap[-28] = NULLP_T, dfaMap[-27] = ZEROP_T, dfaMap[-26] = LISTP_T,
    dfaMap[-25] = SYMBOLP_T, dfaMap[-24] = NUMBERP_T, dfaMap[0]=EOF_T, dfaMap[2]=NEW_LINE;


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
    token_y['t'] = 29,
    token_y['u'] = 30,
    token_y['m'] = 31,
    token_y['b'] = 32,
    token_y['y'] = 33,
    token_y['z'] = 34,
    token_y['g'] = 35;
    

  input.open(filename);

  //Check if the input file is valid. If not print an error.
  if(!input){
    cout << "Error opening file. Try again" << endl;
    system("pause");
  }
  
  //Get the input file line by line into the 'line' string
  stringstream s;
  getline(input, line);
  s << line << ' ';
  while(!input.eof()){
    getline(input, line);
    s << line << ' ';
  }
  line = s.str();
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
  input.close();
}

//The brains of the program. Gets the enumerated token_type
token_type LexicalAnalyzer::GetToken()
{
	char c;
	peek = false;

	int state=0;
	lexeme = "";
	_isnum = 0;
	if(line[0] == ' ' || line[0] == '\n')
	  line.erase(line.begin());
	//Make sure the line isn't empty. This is repeated a few times, probably redundantly just for safety.
	if(!line.empty()){
	  
	  c = line[0];

	  //Remove any whitespace
	  while(c == ' ' || c == '\t' || c == '\n' && !line.empty()){
	    line.erase(line.begin());
	    c = line[0];
	  }
	  
	  if(c == '\n'){
	    line.erase(line.begin());
	    return dfaMap[2];
	  }
	  
	  lexeme += c;
	  if(!line.empty())
	    line.erase(line.begin());
	  
	  if(line.empty()){
	    return dfaMap[0];
	  }
	  
	  
	  
	  //Check for unrecognized symbols
	  if(token_y.find(c) == token_y.end() && !isdigit(c) && !isalpha(c) || c == '$' || c == '_' || c == '~' || c == '`' || c == '?' || c == '%' || c == '!' || c =='&'
	     || c == '^' || c == ':' || c == ';' || c == '}' || c == '{' || c == '@' || c == '|' || c == '#' || c == '"' && c != '\n'){
	    
	    errors++;
	    ReportError(lexeme);
	    return (token_type) -500;
	  }

	  //Another check for whitespace.
	  if(c == ' '){
	    line.erase(line.begin());
	    c = line[0];
	  }
	  
	  bool alpha = isLetter(c);
	  _isnum = isnum(c);

	  peek = mustPeek(c);
	  state = dfa[state][token_y[c]];

	  
	  //While the initial character isn't a guaranteed endstate.
	  while (state > 0 && !line.empty() && c != ' ' && c != '\t') {
	    	    
	    state -= 2;
	    int check = dfa[state][token_y['\'']];  
	    char next;
	    
	    if(!line.empty())
	      next = line[0];
	    isLetter(next);
	    
	    if(alpha && !(isLetter(next) || next == '_' || next == '?' || isnum(next))){
	       state = dfa[state][token_y[next]];
	       break;
	    }

	    //If we have a numlit with a '.' in it already and the next char is also a '.', then break and don't consume.
	    if(_isnum >= 2 && next == '.')
	      break;
	    
	    if (peek == false) {
	      state = dfa[state][token_y[next]];
	    }
	    
	    
	    // prevents -+ and +- issues
	    if ((c == '-' || c == '+') && (next == '-' || next == '+')) {
	      state = dfa[state][token_y[next]];
	      break;
	    }

	    //Deals with a + or - in front of an IDENT_T
	    if((c == '-' || c == '+') && !(isnum(next) || next == '.')){
	      state = dfa[state][token_y[next]];
	      break;
	    }
	    
	    //deals with the >>= isues 
	    if ((check == state && (peek == false) ) && state<0){
	      break;
	    }

	    //Check to fix extra decimals
	    isnum(next);
	    if(c =='.' && next != '#'){
	      state = dfa[state][token_y[c]];
	      break;
	    }

    
	    //Deals with numbers followed by anything other than a number.
	    if(c == '#' && (state == 6) && !(next == '#')){
	      state = dfa[state][token_y[next]];
	      break;
	    }

	    if(c == '#' && (state == 5) && !(next == '#' || next =='.')){
		state = dfa[state][token_y[next]];
		break;
	      }
	    
	    c = line[0];

	    //Fixes an issue with numlits having an extra \n in them
	    if(c != '\n'){
	      lexeme+=c;
	    }
	    
	    isLetter(c);
	    _isnum = isnum(c);
	    if(!line.empty())
	      line.erase(line.begin());

	    
	  if(c == '\n'){
	    line.erase(line.begin());
	    return dfaMap[2];
	  }  
	     //Check for unrecognized symbols
	    if(token_y.find(c) == token_y.end() && !isdigit(c) && !isalpha(c) || c == '$' || c == '~' || c == '`' || c == '%' || c =='!' || c == '&'
	       || c == '^' || c == ':' || c == ';' || c == '}' || c == '{' || c == '@' || c == '|' && c != '\n'){
	      if(line[0] == ' ')
		line.erase(line.begin());
	      errors++;
	      ReportError(lexeme);
	      return (token_type) -500; 	      
	    }

	     	    	    
	    if (peek == true ) {
	      //cout << "peek";
	      state = dfa[state][token_y[c]];
	      
	    }
	  } 
	}
	
	/*check for lone '.' here that could have slipped passed when the logic above thinks its a numlit.
	this is the easiest way to check for it*/
	if(lexeme == "." || lexeme == "!" || lexeme == "%" || lexeme == "&"){
	  errors++;
	  ReportError(lexeme);
	  return (token_type) -500;
	}
	
	token = dfaMap[state];
	
	//Our solution to the issue of having a '?' at the end of a numlit
	if(token == NUMLIT_T && lexeme.back() == '?'){
	  errors++;
	  ReportError(lexeme);
	  return (token_type) -500;
	}
	if(line[0] == ' ' || line[0] == '\n')
	  line.erase(line.begin());
	return token;	       
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
    case NUMBERP_T:
	l = "NUMBERP_T";
	break;
    case SYMBOLP_T:
      l = "SYMBOLP_T";
      break;
    case LISTP_T:
      l = "LISTP_T";
      break;
    case ZEROP_T:
      l = "ZEROP_T";
      break;
    case NULLP_T:
      l = "NULLP_T";
      break;
    case CHARP_T:
      l = "CHARP_T";
      break;
    case STRINGP_T:
      l = "STRINGP_T";
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
      l = "EOF_T";
      break;
    case NUM_TOKENS:
      break;
    case NEW_LINE:
      l = ""; 
    case (token_type)-500:
      return "ERROR_T";
      break;
      
    default:
      break;
    }
 
  return l;
}

string LexicalAnalyzer::GetLexeme () const
{

  return lexeme;
}

void LexicalAnalyzer::ReportError (const string &msg)
{   
  errorReport =  "Error found: " + msg;
}

string LexicalAnalyzer::getErrorReport(){
  return errorReport;
}

bool LexicalAnalyzer::isLetter(char &a){
  if( isupper(a)){
    a = 'A';
    return true;
  }
  if(islower(a)){

    switch(a){
    case 'c':
    case 'o':
    case 'n':
    case 's':
    case 'i':
    case 'f':
    case 'w':
    case 'h':
    case 'l':
    case 'e':
    case 'a':
    case 'd':
    case 'r':
    case 't':
    case 'u':
    case 'm':
    case 'b':
    case 'y':
    case 'z':
    case 'g':
      return true;
    default:
      a = 'A';
      return true;
    }  
  }
 
  
  return false;
}

int LexicalAnalyzer::isnum(char &a) {


	if (isdigit(a)){
		a = '#';
		return 1;
	}
	return 0;

}
int LexicalAnalyzer::mustPeek(char a) {

	if (peek == false) {
	  if(isalpha(a))
	    return 4;
		switch (a)
		{

		case ' ':
		case '\n':
		case '\t':
		  return 3;
		  
		case'#':
			return 2;
		case'.':
		case'-':
		case'+':
			return 1;


		default:
			return 0;
		}
	}
	else
		return false;

}

int LexicalAnalyzer::getErrors(){
  return errors;
}
