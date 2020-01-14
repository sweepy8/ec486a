#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "expr.hpp"

using namespace std;

class Program{
  vector<Expr*> _expressions;

public:
  void addExpression(Expr *expr){
    _expressions.push_back(expr);
  }

  FileDecl * findDecl(string name){
    for(Expr *expr : _expressions){
      FileDecl *decl = dynamic_cast<FileDecl*>(expr);
      if(decl){
	if(decl->isVariableName(name)){
	  return decl;
	}
      }
    }
    
    cerr << "Couldn't find declaration name for: " << name << "\n";
    exit(1);

    // Unreachable
    return NULL;
  }
  
  virtual void run(){
    vector<int> results;
    for(Expr *expr : _expressions){
      results = expr->run();
    }
    cout << "(";
    for(int c = 0; c < results.size(); c++){
      if(c == results.size() - 1){
	cout << results[c];
      }else{
	cout << results[c] << ",";
      }
    }
    cout << ")\n";
  }
};

int main(int argc, char ** argv) {
  if(argc < 2){
    cout << argv[0] << " program.fre\n";
    return 1;
  }

  vector<string> tokens;
  fstream programIn(argv[1]);

  if(!programIn.is_open()){
    cout << "Error: Failed to open program file\n";
  }

  string line;
  string token;
  
  while(getline(programIn, line)){
    stringstream ss(line);
    while(getline(ss,token,' ')){
      tokens.push_back(token);
    }
  }
  
  programIn.close();

  Program *program = new Program();

  // TODO: Parse the tokens into a tree

  program->run();
  
  return 0;
}
