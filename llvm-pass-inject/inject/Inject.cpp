#include "llvm/ADT/StringRef.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instruction.h"
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

  static std::string operand_to_flag(Value *operand) {
    auto operandType = operand->getType();
    // type check
    // Ref: https://stackoverflow.com/a/22163892
    if (operandType->isIntegerTy()) {
      return std::string(", %d");
    } else if (operandType->isFloatTy()) {
      return std::string(", %f");
    } else if (operandType->isDoubleTy()) {
      return std::string(", %lf");
    } else {
      operand->dump();
      return std::string(", %p");
    }
  }

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
      // Instruction *branchInst = BB->getTerminator();
      // MDNode *BrWeightMD = branchInst->getMetadata(LLVMContext::MD_prof);
      for (BasicBlock::iterator BI = BB->begin(), BE = BB->end(); BI != BE;
           ++BI) {

        if (auto CBI = dyn_cast<CallInst>(&(*BI))) {
          errs() << "I saw a CallInst called '"
                 << CBI->getCalledFunction()->getName() << "'";

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
          auto func_name = CBI->getCalledFunction()->getName();
          if (func_name == "printf" || func_name == "llvm.dbg.declare") {
            // prevent error: Running pass 'X86 DAG->DAG Instruction Selection
            // when '-g'
            errs() << " (skip)\n";
            continue;
          }
          errs() << ", ";
          std::string s = std::string("inject printf for call '") +
                          std::string(CBI->getCalledFunction()->getName()) +
                          "'";
          Value *str = builder.CreateGlobalStringPtr(s, "str", 0, M);
          std::vector<Value *> argsV({str});

          // Ref: https://stackoverflow.com/a/40798725
          auto n = CBI->getNumArgOperands();
          errs() << "Num of arguments: " << n << ", ";
          std::string s2 = "";
          for (int i = 0; i < n; ++i) {
            Value *operand = CBI->getArgOperand(i);
            s2 += operand_to_flag(operand);
          }
          s2 += "\n";
          errs() << "format specifier of printf: \"";
          errs().write_escaped(s2) << "\"\n";
          Value *str2 = builder.CreateGlobalStringPtr(s2, "str2", 0, M);
          std::vector<Value *> argsV2({str2});
          for (int i = 0; i < n; ++i) {
            Value *operand = CBI->getArgOperand(i);
            if (operand->getType()->isFloatTy()) {
              // We cannot print float number by printf function if we pass it
              // to the function Ref: https://stackoverflow.com/a/28097654
              errs() << "Add fpext for printing float vaule\n";
              builder.SetInsertPoint(CBI);
              // update operand to the casted version
              operand = builder.CreateCast(Instruction::FPExt, operand,
                                           Type::getDoubleTy(context));
            }
            argsV2.push_back(operand);
          }

          // insert printf right before the call instruction
          builder.SetInsertPoint(CBI);
          builder.CreateCall(M->getFunction("printf"), argsV);
          builder.CreateCall(M->getFunction("printf"), argsV2);
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
