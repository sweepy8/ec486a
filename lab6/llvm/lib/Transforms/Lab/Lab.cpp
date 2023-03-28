#include "llvm/ADT/Statistic.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"

using namespace llvm;

#define DEBUG_TYPE "lab"

namespace {
  struct Lab : public FunctionPass {
    // ID is required by LLVM
    static char ID;
    // _hookType stores the signature of the function we want to call dynamically
    // (i.e. void function_name(char *);)
    FunctionType *_hookType;
    // _beginHook stores a reference to the function "void begin(char*)"
    FunctionCallee _beginHook;
    // _endHook stores a reference to the function "void end(char*)"
    FunctionCallee _endHook;
    // _module is the parent module for the current file being processed
    Module *_module;
    
    Lab() : FunctionPass(ID) {}

    bool doInitialization(Module &M) override {
      _module = &M; // Save the Module in case we need it later

      // Set up the parameter types for the hook function
      Type **types = new Type*[1];
      // getInt8PtrTy gets a char* type (8 bit integer pointer)
      types[0] = Type::getInt8PtrTy(M.getContext());
      // The next function we need to use requires an ArrayRef<Type*> instead of a Type**
      // The second argument needs to match the size of the "types" array created above
      ArrayRef<Type*> args(types,1);

      // Creating the _hookType as a void function with the parameter types set up above
      _hookType = FunctionType::get(Type::getVoidTy(M.getContext()),args,false);

      // Create a FunctionCallee with the name begin and signature _hookType
      _beginHook = M.getOrInsertFunction("begin",_hookType);
      _endHook = M.getOrInsertFunction("end",_hookType);
      
      return true;
    }
    
    bool runOnFunction(Function &F) override {
      BasicBlock &entry = F.getEntryBlock();
      // Create arguments to pass into the "begin" function
      Value **values = new Value*[1];
      llvm::IRBuilder<> builder(entry.getFirstNonPHI());
      values[0] = builder.CreateGlobalStringPtr(F.getName().str().c_str());
      ArrayRef<Value*> args(values,1);

      // Create a call to the "begin" function
      CallInst::Create(_beginHook,args,"",entry.getFirstNonPHI());

      // Loop over all instructions in the function
      for(BasicBlock &BB : F){
	for(Instruction &Inst : BB){
	  // Check for return instructions
	  if(isa<ReturnInst>(&Inst)){
	    // Insert a hook to show the function has ended
	    CallInst::Create(_endHook,args,"",&Inst);
	  }
	}
      }
      
      return true;
    }
  };
}

char Lab::ID = 0;
static RegisterPass<Lab> X("lab", "Lab World Pass");
