#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "llvm/Support/CommandLine.h"

#include <set>
#include <string>

using namespace clang;
using namespace clang::tooling;
using namespace llvm;
using namespace std;

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...\n");

/*
 * This is our derived Visitor class.  Here, we need to implement 
 * any Visit methods for types, decls, stmts, and exprs that we 
 * want to examine.
 */

class ECPerfVisitor : public RecursiveASTVisitor<ECPerfVisitor> {
  ASTContext *_context;
  bool _inMain;
  set<string> _largeVector;

  bool _largeInt;
  bool _push;
public:
  
  explicit ECPerfVisitor(ASTContext *context) : _context(context), _inMain(false) ,_largeInt(false), _push(false){}

  ~ECPerfVisitor(){
    for(string s : _largeVector){
      llvm::outs() << s << "\n";
    }
  }

  bool VisitCallExpr(CallExpr *call){
    Expr *callee = call->getCallee();
    if(callee){
      callee = callee->IgnoreCasts();
      MemberExpr *member = dyn_cast<MemberExpr>(callee);
      if(member){
	member->dump();
      }
    }
    return true;
  }

  bool VisitFunctionDecl(FunctionDecl *decl){
    if(decl->getNameAsString() == "main"){
      _inMain = true;
    }
    return true;
  }
  
  bool VisitIntegerLiteral(IntegerLiteral *intLit){
    if(_inMain){
      if(intLit->getValue().getLimitedValue() > 10000){
	_largeInt = true;
      }else{
	_largeInt = false;
      }
    }
    return true;
  }

  bool VisitCXXMemberCallExpr(CXXMemberCallExpr *expr){
    if(_inMain){
      CXXMethodDecl *decl = expr->getMethodDecl();
      if(decl){
	if(decl->getNameAsString() == "push_back"){
	  _push = true;
	}else{
	  _push = false;
	}
      }
    }
    return true;
  }

  bool VisitDeclRefExpr(DeclRefExpr *declRef){
    if(_inMain){
      ValueDecl *value = declRef->getDecl();
      if(value){
	if(_largeInt && _push){
	  _largeVector.insert(value->getNameAsString());
	  _largeInt = false;
	  _push = false;
	}
      }
    }
    return true;
  }
};

/*
 * This class is the dispatcher part of the Visitor pattern.
 * See "Element" in your notes.  We need to implement a top-level
 * method that allows us to override the base Visitor for each
 * source code file.
 */

class ECPerfConsumer : public clang::ASTConsumer{
  ECPerfVisitor _visitor;

public:
  explicit ECPerfConsumer(ASTContext *context) : _visitor(context) {}
  
  virtual void HandleTranslationUnit(clang::ASTContext& Context){
    _visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }
};

/*
 * This class is the interface between the clang tool library
 * and our code.  You need to create a class that inherits
 * from ASTFrontendAction to run anything on the source code.
 * You also need to override the CreateASTConsumer class as 
 * shown below.
 */

class ECPerf : public clang::ASTFrontendAction{
public:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& Compiler,
								llvm::StringRef InFile) {
    return std::unique_ptr<clang::ASTConsumer>(new ECPerfConsumer(&Compiler.getASTContext()));
  }
};

int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());
  return Tool.run(newFrontendActionFactory<ECPerf>().get());
}
