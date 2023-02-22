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

#include <set>

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

class UninitVisitor : public RecursiveASTVisitor<UninitVisitor> {
  ASTContext *_context;
  std::set<VarDecl*> uninitialized;
  std::set<VarDecl*> initialized;
  
public:
  explicit UninitVisitor(ASTContext *context) : _context(context) {
  }

  ~UninitVisitor(){
  }

  // TODO: Add Visit methods here
  
  
};

class UninitConsumer : public clang::ASTConsumer{
  UninitVisitor _visitor;

public:
  explicit UninitConsumer(ASTContext *context) : _visitor(context) {}

  virtual void HandleTranslationUnit(clang::ASTContext& Context) override {
    _visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }
};

class Uninit : public clang::ASTFrontendAction{
public:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& Compiler,
								llvm::StringRef InFile) override {
    return std::unique_ptr<clang::ASTConsumer>(new UninitConsumer(&Compiler.getASTContext()));
  }
};

int main(int argc, const char **argv) {
  llvm::Expected<CommonOptionsParser> OptionsParserE = CommonOptionsParser::create(argc, argv, MyToolCategory);
  CommonOptionsParser& OptionsParser = OptionsParserE.get();
  ClangTool Tool(OptionsParser.getCompilations(),
		 OptionsParser.getSourcePathList());
  return Tool.run(newFrontendActionFactory<Uninit>().get());
}
