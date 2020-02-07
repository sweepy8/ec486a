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

class LoopInfo{
public:
  std::string _file;
  int _start;
  int _end;
  int _nested;

  LoopInfo() : _start(0),_end(0),_nested(1) {}
};

class LoopsVisitor : public RecursiveASTVisitor<LoopsVisitor> {
  ASTContext *_context;
  bool _inMain;

  std::vector<LoopInfo> loops;
  
public:
  
  explicit LoopsVisitor(ASTContext *context) : _context(context), _inMain(false) {}

  ~LoopsVisitor(){
    for(LoopInfo loop : loops){
      llvm::outs() << loop._file << ":" << loop._start << " has complexity O(N^" << loop._nested << ")\n";
    }
  }

  bool VisitFunctionDecl(FunctionDecl *decl){
    if(decl->getNameAsString() == "main"){
      _inMain = true;
    }
    return true;
  }

  bool VisitForStmt(ForStmt *forStmt){
    LoopInfo info;
    
    SourceLocation loc = forStmt->getBeginLoc();   
    std::string s = loc.printToString(_context->getSourceManager());

    size_t loc1 = s.find(":");
    size_t loc2 = s.find_last_of(":");
    info._file = s.substr(0,loc1);
    info._start = std::stoi(s.substr(loc1+1,loc2-2));

    loc = forStmt->getEndLoc();   
    s = loc.printToString(_context->getSourceManager());

    loc1 = s.find(":");
    loc2 = s.find_last_of(":");

    info._end = std::stoi(s.substr(loc1+1,loc2-2));

    bool nested = false;

    for(LoopInfo& l : loops){
      if(l._file.compare(info._file) == 0){
	if(l._start <= info._start && l._end >= info._end){
	  nested = true;
	  l._nested++;
	  break;
	}
      }
    }

    if(!nested){
      loops.push_back(info);
    }
    
    return true;
  }

  bool VisitWhileStmt(WhileStmt *whileStmt){
    SourceLocation loc = whileStmt->getBeginLoc();   
    std::string s = loc.printToString(_context->getSourceManager());
    //llvm::outs() << s << "\n";

    return true;
  }
};

/*
 * This class is the dispatcher part of the Visitor pattern.
 * See "Element" in your notes.  We need to implement a top-level
 * method that allows us to override the base Visitor for each
 * source code file.
 */

class LoopsConsumer : public clang::ASTConsumer{
  LoopsVisitor _visitor;

public:
  explicit LoopsConsumer(ASTContext *context) : _visitor(context) {}
  
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

class Loops : public clang::ASTFrontendAction{
public:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& Compiler,
								llvm::StringRef InFile) {
    return std::unique_ptr<clang::ASTConsumer>(new LoopsConsumer(&Compiler.getASTContext()));
  }
};

int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());
  return Tool.run(newFrontendActionFactory<Loops>().get());
}
