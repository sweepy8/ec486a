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
  
  return 0;
}
