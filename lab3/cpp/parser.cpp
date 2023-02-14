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

  void addToken(Token token)
  {
    tokens.push_back(token);
  }

  void print()
  {
    pad();
    std::cout << statementClass << "\n";
    spaces += padIncrement;
    for(Token token : tokens)
    {
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

//class token
bool classT(Statement *stmt, Token token)
{
  if(token.tokenClass == "class")
  {
    stmt->addToken(token);
    return true;
  }
  else
  {
    std::cerr << "Syntax error at token: " << token.original << "\n";
    return false;
  }
}

//class name token
bool classnameT(Statement *stmt, Token token)
{
  if(token.tokenClass == "classname")
  {
    stmt->addToken(token);
    return true;
  }
  else
  {
    std::cerr << "Syntax error at token: " << token.original << "\n";
    return false;
  }
}

//lab token
bool labT(Statement *stmt, Token token)
{
  if(token.tokenClass == "lab")
  {
    stmt->addToken(token);
    return true;
  }
  else
  {
    std::cerr << "Syntax error at token: " << token.original << "\n";
    return false;
  }
}

// lab name token
bool labnameT(Statement *stmt, Token token)
{
  if(token.tokenClass == "labname")
  {
    stmt->addToken(token);
    return true;
  }
  else
  {
    std::cerr << "Syntax error at token: " << token.original << "\n";
    return false;
  }
}

// remind token
bool remindT(Statement *stmt, Token token)
{
  if(token.tokenClass == "remind")
  {
    stmt->addToken(token);
    return true;
  }
  else
  {
    std::cerr << "Syntax error at token: " << token.original << "\n";
    return false;
  }
}

// freq time token
bool freqtimeT(Statement *stmt, Token token)
{
  if(token.tokenClass == "freqtime")
  {
    stmt->addToken(token);
    return true;
  }
  else
  {
    std::cerr << "Syntax error at token: " << token.original << "\n";
    return false;
  }
}

//due date token
bool duedateT(Statement *stmt, Token token)
{
  if(token.tokenClass == "duedate")
  {
    stmt->addToken(token);
    return true;
  }
  else
  {
    std::cerr << "Syntax error at token: " << token.original << "\n";
    return false;
  }
}

// date token
bool dateT(Statement *stmt, Token token)
{
  if(token.tokenClass == "date")
  {
    stmt->addToken(token);
    return true;
  }
  else
  {
    std::cerr << "Syntax error at token: " << token.original << "\n";
    return false;
  }
}

bool accept(Token token, std::list<Token> tokens)
{
  //create class ec486
  if(token.tokenClass == "create")
  {
    Statement *stmt = new Statement("createcall");
    stmt->addToken(token);
    statements.push_back(stmt);
    Token nextToken = tokens.front();
    tokens.pop_front();
    if(classT(stmt,nextToken))
    {
      nextToken = tokens.front();
      tokens.pop_front();
      if(classnameT(stmt,nextToken))
      {
        if(!tokens.empty())
        {
  	       nextToken = tokens.front();
  	       tokens.pop_front();
  	       return accept(nextToken, tokens);
        }
        else
        {
  	       return true;
        }
      }
    }
    //create lab lab2 ec486
    else if(labT(stmt,nextToken))
    {
      nextToken = tokens.front();
      tokens.pop_front();
      if(labnameT(stmt,nextToken))
      {
        nextToken = tokens.front();
        tokens.pop_front();
        if(classnameT(stmt,nextToken))
        {
          if(!tokens.empty())
          {
  	          nextToken = tokens.front();
  	          tokens.pop_front();
  	          return accept(nextToken, tokens);
          }
          else
          {
  	          return true;
          }
        }
      }
    }
    else
    {
      // If we get here, nothing matched
      std::cerr << "Syntax error at token: " << token.original << "\n";
      return false;
    }
  }

  //assign remind daily0900 lab2
  if(token.tokenClass == "assign")
  {
    Statement *stmt = new Statement("assigncall");
    stmt->addToken(token);
    statements.push_back(stmt);
    Token nextToken = tokens.front();
    tokens.pop_front();
    if(remindT(stmt,nextToken))
    {
      nextToken = tokens.front();
      tokens.pop_front();
      if(freqtimeT(stmt,nextToken))
      {
        nextToken = tokens.front();
        tokens.pop_front();
        if(labnameT(stmt,nextToken))
        {
          if(!tokens.empty())
          {
  	          nextToken = tokens.front();
  	          tokens.pop_front();
  	          return accept(nextToken, tokens);
          }
          else
          {
  	          return true;
          }
        }
      }
    }
    //assign due_date 06FEB23 lab2
    else if(duedateT(stmt,nextToken))
    {
      nextToken = tokens.front();
      tokens.pop_front();
      if(dateT(stmt,nextToken))
      {
        nextToken = tokens.front();
        tokens.pop_front();
        if(labnameT(stmt,nextToken))
        {
          if(!tokens.empty())
          {
              nextToken = tokens.front();
              tokens.pop_front();
              return accept(nextToken, tokens);
          }
          else
          {
              return true;
          }
        }
      }
    }
    else
    {
      // If we get here, nothing matched
      std::cerr << "Syntax error at token: " << token.original << "\n";
      return false;
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

  while(std::getline(file,line))
  {
    cmatch what;
    //create class ec486
    regex expr1("\\s*(create)\\s*(\\w+)\\s*(\\w+)\\s*");
    //create lab lab2 ec486
    regex expr2("\\s*(create)\\s*(\\w+)\\s*(\\w+)\\s*(\\w+)\\s*");
    //assign remind daily0900 lab2
    regex expr3("\\s*(assign)\\s*(remind)\\s*(\\w+)\\s*(\\w+)\\s*");
    //assign duedate 06FEB23 lab2
    regex expr4("\\s*(assign)\\s*(\\w+)\\s*(\\w+)\\s*(\\w+)\\s*");

    //create class ec486
    if(regex_match(line.c_str(),what,expr1))
    {
      Token tok1;
      tok1.original = what[1];
      tok1.tokenClass = "create";
      Token tok2;
      tok2.original = what[2];
      tok2.tokenClass = "class";
      Token tok3;
      tok3.original = what[3];
      tok3.tokenClass = "classname";
      tokens.push_back(tok1);
      tokens.push_back(tok2);
      tokens.push_back(tok3);
    }
    //create lab lab2 ec486
    else if(regex_match(line.c_str(),what,expr2))
    {
      Token tok1;
      tok1.original = what[1];
      tok1.tokenClass = "create";
      Token tok2;
      tok2.original = what[2];
      tok2.tokenClass = "lab";
      Token tok3;
      tok3.original = what[3];
      tok3.tokenClass = "labname";
      Token tok4;
      tok4.original = what[4];
      tok4.tokenClass = "classname";
      tokens.push_back(tok1);
      tokens.push_back(tok2);
      tokens.push_back(tok3);
      tokens.push_back(tok4);
    }
    //assign due_date 06FEB23 lab2
    else if(regex_match(line.c_str(),what,expr3))
    {
      Token tok1;
      tok1.original = what[1];
      tok1.tokenClass = "assign";
      Token tok2;
      tok2.original = what[2];
      tok2.tokenClass = "remind";
      Token tok3;
      tok3.original = what[3];
      tok3.tokenClass = "freqtime";
      Token tok4;
      tok4.original = what[4];
      tok4.tokenClass = "labname";
      tokens.push_back(tok1);
      tokens.push_back(tok2);
      tokens.push_back(tok3);
      tokens.push_back(tok4);
    }
    //assign remind daily0900 lab2
    else if(regex_match(line.c_str(),what,expr4))
    {
      Token tok1;
      tok1.original = what[1];
      tok1.tokenClass = "assign";
      Token tok2;
      tok2.original = what[2];
      tok2.tokenClass = "duedate";
      Token tok3;
      tok3.original = what[3];
      tok3.tokenClass = "date";
      Token tok4;
      tok4.original = what[4];
      tok4.tokenClass = "labname";
      tokens.push_back(tok1);
      tokens.push_back(tok2);
      tokens.push_back(tok3);
      tokens.push_back(tok4);
    }
    else
    {
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
