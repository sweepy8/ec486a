#pragma once

#include <string>
#include <vector>

class Expr{
public:
  virtual std::vector<int> run() = 0;
  virtual void addExpression(Expr *expr) {}
};

class FileDecl : public Expr{
  std::string _variableName;
  std::string _fileName;
  std::vector<int> _values;
  
public:
  virtual std::vector<int> run();
  std::vector<int> getValues();
  bool isVariableName(std::string variableName);
  void setVariableName(std::string variableName);
  void setFileName(std::string fileName);
};

class FileExpr : public Expr{
  FileDecl *_declaration;

public:
  FileExpr(FileDecl *declaration);
  virtual std::vector<int> run();
};

class ReduceExpr : public Expr{
  std::vector<Expr *> _expressions;
public:
  virtual std::vector<int> run();
  virtual void addExpression(Expr *expr);
  virtual int reduce(int x, int y) = 0;
};

class PlusExpr : public ReduceExpr{
public:
  virtual int reduce(int x, int y);
};

class MultiplyExpr : public ReduceExpr{
public:
  virtual int reduce(int x, int y);
};

class MaxExpr : public ReduceExpr{
public:
  virtual int reduce(int x, int y);
};

class MinExpr : public ReduceExpr{
public:
  virtual int reduce(int x, int y);
};

class SubExpr : public ReduceExpr{
public:
  virtual int reduce(int x, int y);
};
