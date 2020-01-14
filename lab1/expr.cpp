#include <fstream>
#include <iostream>
#include "expr.hpp"

using namespace std;

vector<int> FileDecl::run(){
  fstream input(_fileName);
  int i;
  
  while(input >> i){
    _values.push_back(i);
  }
  
  return _values;
}

vector<int> FileDecl::getValues(){
  return _values;
}

bool FileDecl::isVariableName(string variableName){
  return variableName.compare(_variableName) == 0;
}

void FileDecl::setVariableName(string variableName){
  _variableName = variableName;
}

void FileDecl::setFileName(string fileName){
  _fileName = fileName;
}

FileExpr::FileExpr(FileDecl *declaration) : _declaration(declaration) {}

vector<int> FileExpr::run(){
  return _declaration->getValues();
}


vector<int> ReduceExpr::run(){
  if(_expressions.size() == 0){
    cerr << "Error! No sub-expression for reduce!\n";
    exit(1);
  }else if(_expressions.size() == 1){
    // Run sub-expression and compute on results
    vector<int> results = _expressions[0]->run();
    int result = results[0];
    
    if(results.size() == 1){
      return results;
    }
    
    for(int c = 1; c < results.size(); c++){
      result = this->reduce(result,results[c]);
    }
    
    vector<int> myres;
    myres.push_back(result);
    
    return myres;
  }else{
    // Run reduce on all sub-expressions
    vector<int> results;
    for(Expr *expr : _expressions){
      vector<int> sub = expr->run();
      
      if(sub.size() == 1){
	return sub;
      }
      
      int result = sub[0];
      
      for(int c = 1; c < sub.size(); c++){
	result = this->reduce(result,sub[c]);
      }
      results.push_back(result);
    }
    return results;
  }
}

void ReduceExpr::addExpression(Expr *expr){
  _expressions.push_back(expr);
}

int PlusExpr::reduce(int x, int y){
  return x + y;
}

int MultiplyExpr::reduce(int x, int y){
  return x * y;
}

int MaxExpr::reduce(int x, int y){
  if(x > y){
    return x;
  }else{
    return y;
  }
}

int MinExpr::reduce(int x, int y){
  if(x < y){
    return x;
  }else{
    return y;
  }
}
