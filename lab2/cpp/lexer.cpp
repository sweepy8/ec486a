#include <stdlib.h>
#include <boost/regex.hpp>
#include <string>
#include <list>
#include <iostream>
#include <fstream>

using namespace boost;

typedef struct Token
{
  std::string original;
  std::string tokenClass;
}

Token;

int main(int argc, char **argv)
{
  if(argc < 2)
  {
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
    //assign remind daily0900 lab2
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
    //assign due_date 06FEB23 lab2
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
  for(Token tok : tokens)
  {
    std::cout << tok.tokenClass << " - " << tok.original << "\n";
  }

  return 0;
}
