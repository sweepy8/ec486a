#include "llvm/IR/IRBuilder.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
using namespace llvm;

#define DEBUG_TYPE "lab"

namespace {
  // Hello - The first implementation, without getAnalysisUsage.
  struct Lab : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    FunctionType *_hookType;
    FunctionCallee _beginHook;
    FunctionCallee _endHook;
    Module *_module;

    Lab() : FunctionPass(ID) {}

    bool doInitialization(Module &M) override {
      _module = &M;
      Type **types = new Type*[1];
      types[0] = Type::getInt8PtrTy(M.getContext());
      ArrayRef<Type*> args(types,1);
      _hookType = FunctionType::get(Type::getVoidTy(M.getContext()),args,false);
      _beginHook = M.getOrInsertFunction("begin",_hookType);
      _endHook = M.getOrInsertFunction("end",_hookType);

      return false;
    }

    bool runOnFunction(Function &F) override {
      BasicBlock &entry = F.getEntryBlock();
      Value **values = new Value*[1];
      llvm::IRBuilder<> builder(entry.getFirstNonPHI());
      values[0] = builder.CreateGlobalStringPtr(F.getName().str().c_str());
      ArrayRef<Value*> args(values,1);
      CallInst::Create(_beginHook,args,"",entry.getFirstNonPHI());

      for(BasicBlock &BB : F){
        for(Instruction &Inst : BB){
          if(isa<ReturnInst>(Inst)){
            CallInst::Create(_endHook,args,"",&Inst);
          }
        }
      }

      return true;
    }
  };
}

char Lab::ID;
static RegisterPass<Lab> X("lab", "Lab Pass");

static void registerMyPass(const PassManagerBuilder &,
                           llvm::legacy::PassManagerBase &PM) {
    PM.add(new Lab());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerMyPass);
