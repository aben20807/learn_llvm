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
  Value *pFile;
  StructType *IO_FILE_ty;
  Type *IO_FILE_PTR_ty;

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
          auto func_name = CBI->getCalledFunction()->getName();
          errs() << "I saw a CallInst called '" << func_name << "'";

          // Declare C standard library fprintf
          Type *IO_FILE_ty =
              StructType::create(M->getContext(), "struct._IO_FILE");
          Type *IO_FILE_PTR_ty = PointerType::getUnqual(IO_FILE_ty);
          Type *intType = Type::getInt32Ty(context);
          std::vector<Type *> fprintfArgsTypes(
              {IO_FILE_PTR_ty, Type::getInt8PtrTy(context)});
          FunctionType *fprintfType =
              FunctionType::get(intType, fprintfArgsTypes, true);
          llvm::Constant *fprintfFunc = Function::Create(
              fprintfType, Function::ExternalLinkage, "fprintf", M);

          // value of the injected printf function
          // get the called function name
          // Ref: https://stackoverflow.com/a/11687221
          if (func_name == "printf" || func_name == "fprintf" ||
              func_name.startswith("llvm") || func_name == "clock_gettime" ||
              func_name.startswith("omp") || func_name.startswith("__kmpc")) {
            // skipping llvm functions is to prevent error: Running pass 'X86
            // DAG->DAG Instruction Selection when '-g'
            errs() << " (skip)\n";
            continue;
          }
          errs() << ", ";
          std::string s = std::string("inject printf for call '") +
                          std::string(func_name) + "'";
          Value *str = builder.CreateGlobalStringPtr(s, "str", 0, M);
          Value *global_var_stderr =
              M->getOrInsertGlobal("stderr", IO_FILE_PTR_ty);
          // need to load stderr first
          // Ref: https://godbolt.org/z/ac73f8oPs
          builder.SetInsertPoint(CBI);
          auto loaded_stderr =
              builder.CreateLoad(IO_FILE_PTR_ty, global_var_stderr);
          if (global_var_stderr == nullptr) {
            errs() << "null\n\n\n\n";
          }
          std::vector<Value *> argsV({loaded_stderr, str});

          // get operands from the call inst
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
          std::vector<Value *> argsV2({loaded_stderr, str2});
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
          builder.CreateCall(M->getFunction("fprintf"), argsV);
          builder.CreateCall(M->getFunction("fprintf"), argsV2);

          // Type *voidType = Type::getVoidTy(context);
          // FunctionType *gettimestampType = FunctionType::get(voidType, false);
          // llvm::Constant *gettimestampFunc = Function::Create(
          //     gettimestampType, Function::ExternalLinkage, "gettimestamp", M);
          // builder.SetInsertPoint(CBI);
          // builder.CreateCall(M->getFunction("gettimestamp"), argsV2);
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
