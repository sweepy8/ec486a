/* Tom Hawkins 
 * Lab1 -- EC486A
 * Parts 1 & 2 
 * Extra functionality is that this interpreter can handle 
 * an arbitrary amount of infix operations, provided it is 
 * all on one line
*/ 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>


#include "expr.hpp"

using namespace std;
unordered_set<string> keywords = {"file","max","min","+","*"};
unordered_set<string> varNames = {};

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
  vector<Expr*> currExpr;

  for(int i = 0; i < tokens.size(); i++){
    
    //Token fmust be a variable name
    if(keywords.count(tokens[i]) == 0) {
        
        if(varNames.count(tokens[i]) == 0 ) { cout << "Error: No definition for var named " << tokens[i] << endl; exit(1);}    
        FileDecl* tmp = program->findDecl(tokens[i]);
        FileExpr* tfe = new FileExpr(tmp);
        (currExpr.back())->addExpression(tfe);
        


    //Token must be a keyword
    } else {

        //Inelegant brute force way of dealing with file decles
        if(tokens[i].compare("file") == 0 ) {
            i = i + 1;
            if(varNames.count(tokens[i]) != 0) {cout << "Error: multiple definitions of var name " << tokens[i] << endl; exit(1);}
            if(keywords.count(tokens[i]) != 0) {cout << "Error: inalid use of keyword " << tokens[i] << endl; exit(1);}

            varNames.insert(tokens[i]);       //Record the variable
            FileDecl *decl = new FileDecl();  //Create a file decl
            decl->setVariableName(tokens[i]); //add the variable name

            i = i + 1;
            decl->setFileName(tokens[i]);    //Add the file name
            program->addExpression(decl);

        } else if (tokens[i].compare("+") == 0 ) {
            PlusExpr* tmp = new PlusExpr();
            if(currExpr.size() != 0){                   
                (currExpr.back())->addExpression(tmp);  //Add this new expr as an expression of the most recent expr we've seen
                currExpr.push_back(tmp);                //Update the vector so that this new expr is now the most recent one we've seen
            }else {
                currExpr.push_back(tmp);                //Special case where this is the first expr we've seen, just add it to the list of exprs
            }
        } else if (tokens[i].compare("*") == 0 ) {      //Ditto for the rest of the expr types
            MultiplyExpr* tmp = new MultiplyExpr();
            if(currExpr.size() != 0) {
                (currExpr.back())->addExpression(tmp);
                currExpr.push_back(tmp);
            }else {
                currExpr.push_back(tmp);
            }
        } else if (tokens[i].compare("max") == 0 ) {
            MaxExpr* tmp = new MaxExpr();
            if(currExpr.size() != 0) {
                (currExpr.back())->addExpression(tmp);
                currExpr.push_back(tmp);
            }else {
                currExpr.push_back(tmp);
            }
        } else if (tokens[i].compare("min") == 0 ) {
            MinExpr* tmp = new MinExpr();
            if(currExpr.size() != 0) {
                (currExpr.back())->addExpression(tmp);
                currExpr.push_back(tmp);
            }else {
                currExpr.push_back(tmp);
            }
        }




        }
    
  }
 
  program->addExpression(currExpr.front()); //Add the root of the "tree" of expressions to the program. 
  program->run();

  delete program;
  
  return 0;
}
