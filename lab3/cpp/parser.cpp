#include <stdlib.h>
#include <boost/regex.hpp>
#include <string>
#include <list>
#include <iostream>
#include <fstream>

using namespace boost;

typedef struct Token{
  std::string original;
  std::string tokenClass;
} Token;

const int padIncrement = 2;
int spaces = 0;

void pad(){
  for(int c = 0; c < spaces; c++){
    std::cout << " ";
  }
}

class Statement{
  std::string statementClass;
  std::list<Token> tokens;

public:
  Statement(std::string _statementClass) : statementClass(_statementClass){}

  void addToken(Token token){
    tokens.push_back(token);
  }

  void print(){
    pad();
    std::cout << statementClass << "\n";
    spaces += padIncrement;
    for(Token token : tokens){
      pad();
      std::cout << token.tokenClass << "\n";
      spaces += padIncrement;
      pad();
      std::cout << token.original << "\n";
      spaces -= padIncrement;
    }
    spaces -= padIncrement;
  }
};

std::list<Statement*> statements;

bool argument(Statement *stmt, Token token){
  if(token.tokenClass == "ARGUMENT"){
    stmt->addToken(token);
    return true;
  }else{
    std::cerr << "Syntax error at token: " << token.original << "\n";
    return false;
  }
}

bool accept(Token token, std::list<Token> tokens){
  if(token.tokenClass == "FUNCTION"){
    Statement *stmt = new Statement("FunctionCall");
    stmt->addToken(token);
    statements.push_back(stmt);
    Token nextToken = tokens.front();
    tokens.pop_front();
    if(argument(stmt,nextToken)){
      if(!tokens.empty()){
	nextToken = tokens.front();
	tokens.pop_front();
	return accept(nextToken, tokens);
      }else{
	return true;
      }
    }
  }
  // If we get here, nothing matched
  std::cerr << "Syntax error at token: " << token.original << "\n";
  return false;
}

int main(int argc, char **argv){
  if(argc < 2){
    std::cout << "Usage: " << argv[0] << " [file_name]\n";
    return 1;
  }
  
  char *filename = argv[1];
  std::fstream file(filename,std::fstream::in);

  std::list<Token> tokens;
  std::string line;

  while(std::getline(file,line)){
    cmatch what;
    regex expression("(\\w+)\\((\\w+)\\)");
    if(regex_match(line.c_str(),what,expression)){
      Token tok1;
      tok1.original = what[1];
      tok1.tokenClass = "FUNCTION";
      Token tok2;
      tok2.original = what[2];
      tok2.tokenClass = "ARGUMENT";
      tokens.push_back(tok1);
      tokens.push_back(tok2);
    }else{
      std::cout << "Syntax error on line: " << line << "\n";
      return 1;
    }
  }

  std::cout << "Found tokens\n";
  std::cout << "-----------------------\n";
  for(Token tok : tokens){
    std::cout << tok.tokenClass << " - " << tok.original << "\n";
  }

  std::cout << "\n\nConstructing an Abstract Syntax Tree\n\n";

  Token firstToken = tokens.front();
  tokens.pop_front();
  bool accepted = accept(firstToken, tokens);

  if(accepted){
    std::cout << "\n\nFinal Abstract Syntax Tree\n\n";
    for(Statement *stmt : statements){
      stmt->print();
    }
  }else{
    std::cout << "Failed to parse file: " << argv[1] << "\n";
  }
  
  return 0;
}
