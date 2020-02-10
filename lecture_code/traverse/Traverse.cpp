#include "clang/Analysis/CFG.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "llvm/Support/CommandLine.h"

#include <cstring>
#include <sstream>

using namespace clang;
using namespace clang::tooling;
using namespace llvm;

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...\n");

class TraverseVisitor : public RecursiveASTVisitor<TraverseVisitor> {
  ASTContext *_context;
  Rewriter *_rewriter;
public:
  explicit TraverseVisitor(ASTContext *context) : _context(context) {
    LangOptions LO;
    _rewriter = new Rewriter(_context->getSourceManager(),LO);
  }

  ~TraverseVisitor(){
    _rewriter->overwriteChangedFiles();
    delete _rewriter;
  }

  bool TraverseFunctionDecl(FunctionDecl *functionDecl){
    llvm::outs() << "Starting Traverse for FunctionDecl: " << functionDecl->getNameAsString() << "\n";
    RecursiveASTVisitor<TraverseVisitor>::TraverseFunctionDecl(functionDecl);
    llvm::outs() << "Finishing Traverse for FunctionDecl: " << functionDecl->getNameAsString() << "\n";
    return true;
  }

  bool WalkUpFromFunctionDecl(FunctionDecl *functionDecl){
    llvm::outs() << "Starting WalkUp for FunctionDecl: " << functionDecl->getNameAsString() << "\n";
    RecursiveASTVisitor<TraverseVisitor>::WalkUpFromFunctionDecl(functionDecl);
    llvm::outs() << "Finishing WalkUp for FunctionDecl: " << functionDecl->getNameAsString() << "\n";
    return true;
  }
  
  bool VisitFunctionDecl(FunctionDecl *functionDecl){
    llvm::outs() << "Visiting FunctionDecl: " << functionDecl->getNameAsString() << "\n";
    return true;
  }
  
  bool TraverseCallExpr(CallExpr *callExpr){
    FunctionDecl *functionDecl = callExpr->getDirectCallee();
    if(functionDecl){
      llvm::outs() << "Starting Traverse for CallExpr: " << functionDecl->getNameAsString() << "()\n";
      RecursiveASTVisitor<TraverseVisitor>::TraverseCallExpr(callExpr);
      llvm::outs() << "Finishing Traverse for CallExpr: " << functionDecl->getNameAsString() << "()\n";
    }
    return true;
  }

  bool WalkUpFromCallExpr(CallExpr *callExpr){
    FunctionDecl *functionDecl = callExpr->getDirectCallee();
    if(functionDecl){
      llvm::outs() << "Starting WalkUp for CallExpr: " << functionDecl->getNameAsString() << "()\n";
      RecursiveASTVisitor<TraverseVisitor>::WalkUpFromCallExpr(callExpr);
      llvm::outs() << "Finishing WalkUp for CallExpr: " << functionDecl->getNameAsString() << "()\n";
    }
    return true;
  }
  
  bool VisitCallExpr(CallExpr *callExpr){
     FunctionDecl *functionDecl = callExpr->getDirectCallee();

     if(functionDecl){
       llvm::outs() << "Visiting CallExpr: " << functionDecl->getNameAsString() << "()\n";
     }
     
     return true;
  }
};

class TraverseConsumer : public clang::ASTConsumer{
  TraverseVisitor _visitor;

public:
  explicit TraverseConsumer(ASTContext *context) : _visitor(context) {}
  
  virtual void HandleTranslationUnit(clang::ASTContext& Context){
    _visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }
};

class Traverse : public clang::ASTFrontendAction{
public:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& Compiler,
								llvm::StringRef InFile) {
    return std::unique_ptr<clang::ASTConsumer>(new TraverseConsumer(&Compiler.getASTContext()));
  }
};

int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());
  return Tool.run(newFrontendActionFactory<Traverse>().get());
}
