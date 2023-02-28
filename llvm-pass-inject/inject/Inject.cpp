#include "llvm/ADT/StringRef.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
using namespace llvm;

namespace {
struct InjectPass : public FunctionPass {
  static char ID;
  InjectPass() : FunctionPass(ID) {}

  virtual bool runOnFunction(Function &F) {
    // Use context
    // Ref: https://stackoverflow.com/q/49558395
    Module *M = F.getParent();
    LLVMContext &context = M->getContext();
    IRBuilder<> builder(context);

    errs() << "I saw a function called '" << F.getName()
           << "', arg_size: " << F.arg_size() << "\n";

    // iterate F, BB
    // Ref: https://stackoverflow.com/q/51082081
    for (Function::iterator BB = F.begin(), E = F.end(); BB != E; ++BB) {
      errs() << "I saw a block called '" << BB->getName() << "'\n";
      Instruction *branchInst = BB->getTerminator();
      MDNode *BrWeightMD = branchInst->getMetadata(LLVMContext::MD_prof);
      for (BasicBlock::iterator BI = BB->begin(), BE = BB->end(); BI != BE;
           ++BI) {

        if (isa<CallInst>(&(*BI))) {
          // auto n = (*BI).getNumOperands();
          // for (int i = 0; i < n; ++i) {
          //   errs() << i << (*BI).getOperand(i)->getName() << "\n";
          // }
          // Declare C standard library printf
          Type *intType = Type::getInt32Ty(context);
          std::vector<Type *> printfArgsTypes({Type::getInt8PtrTy(context)});
          FunctionType *printfType =
              FunctionType::get(intType, printfArgsTypes, true);
          llvm::Constant *printfFunc = Function::Create(
              printfType, Function::ExternalLinkage, "printf", M);

          // value of the injected printf function
          // get the called function name
          // Ref: https://stackoverflow.com/a/11687221
          std::string s =
              std::string("inject printf for call '") +
              std::string(cast<CallInst>(*BI).getCalledFunction()->getName()) +
              std::string("'\n");
          Value *str = builder.CreateGlobalStringPtr(s, "str", 0, M);
          std::vector<Value *> argsV({str});

          // insert printf right before the call instruction
          builder.SetInsertPoint(&*BI);
          builder.CreateCall(M->getFunction("printf"), argsV);
        }
      }
    }
    return true;
  }
};
} // namespace

char InjectPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerInjectPass(const PassManagerBuilder &,
                               legacy::PassManagerBase &PM) {
  PM.add(new InjectPass());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerInjectPass);
