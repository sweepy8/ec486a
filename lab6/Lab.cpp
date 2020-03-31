#include "llvm/ADT/Statistic.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include <map>
#include <set>

using namespace llvm;

#define DEBUG_TYPE "lab"

namespace {
  struct Lab : public BasicBlockPass {
    static char ID;
    
    Lab() : BasicBlockPass(ID) {}
    
    bool runOnBasicBlock(BasicBlock &BB) override {
      // This map should store the values that we can
      // replace with a constant
      std::map<Value*,ConstantInt*> constants;

      // This should hold any alloca instructions that
      // we can eliminate from the code
      std::set<Instruction*> killDefs;
      
      // This should hold any load, store, and other
      // operations that we can remove from the code
      std::set<Instruction*> killUses;
      
      for(Instruction& I : BB){
	Instruction *inst = &I;

	// TODO: Your code goes here
      }

      /*
       * Remove this comment when you're ready to start
       * working on part 2 of the lab (leave the // comments)

      // We remove uses before definitions so LLVM doesn't
      // yell at us
      for(Instruction *I : killUses){
        // eraseFromParent completely removes an instruction 
        // from the IR
	I->eraseFromParent();
      }

      for(Instruction *I : killDefs){
	I->eraseFromParent();
      }
      */
      
      return true;
    }
  };
}

char Lab::ID = 0;
static RegisterPass<Lab> X("optlab", "Optimization Lab Pass");
