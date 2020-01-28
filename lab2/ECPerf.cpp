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
public:
  
  explicit ECPerfVisitor(ASTContext *context) : _context(context) {}

  ~ECPerfVisitor(){
    // TODO: Output results here
    llvm::outs() << "Done\n";
  }
  
  // TODO: Add Visit methods here
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
