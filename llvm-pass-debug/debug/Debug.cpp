#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include <regex>
#include <sstream>

using namespace llvm;

// Ref: https://stackoverflow.com/a/37951305
std::string do_replace( std::string& in, std::string from, std::string to )
{
  return std::regex_replace( in, std::regex(from), to );
}

namespace {
struct DebugPass : public FunctionPass {
  static char ID;
  DebugPass() : FunctionPass(ID) {}

  virtual bool runOnFunction(Function &F) {
    errs() << "I saw a function called '" << F.getName()
           << "', arg_size: " << F.arg_size() << "\n";

    // Ref: https://stackoverflow.com/a/65013686
    std::string str;
    llvm::raw_string_ostream rso(str);
    SmallVector<std::pair<unsigned, MDNode *>, 4> MDs;
    F.getAllMetadata(MDs);
    for (auto &MD : MDs) {
      if (MDNode *N = MD.second) {
        // hiding the address to prevent frequently update the README
        if (const auto *subProgram = dyn_cast<DISubprogram>(N)) {
          rso << "v1:\n" << *subProgram << "\n";
          errs() << do_replace(rso.str(), "<[a-zA-Z_0-9]*>", "<addr>");
          errs() << "func name: " << subProgram->getName() << "\n";
          errs() << "src line:  " << subProgram->getLine() << "\n";
          errs() << "src file:  " << subProgram->getFilename() << "\n";
        }
      }
    }

    // Better?
    const auto *subProgram = F.getSubprogram();
    rso << "v2:\n" << *subProgram << "\n";
    errs() << do_replace(rso.str(), "<[a-zA-Z_0-9]*>", "<addr>");
    errs() << "func name: " << subProgram->getName() << "\n";
    errs() << "src line:  " << subProgram->getLine() << "\n";
    errs() << "src file:  " << subProgram->getFilename() << "\n\n";
    

    for (auto &BB : F) {
      // Instruction *BranchInst = BB.getTerminator();
      // MDNode *BrWeightMD = BranchInst->getMetadata(LLVMContext::MD_dbg);
      // if (BrWeightMD == nullptr) continue;
      // errs() << BrWeightMD->getNumOperands() << "\n\n";
      // if (BrWeightMD->getNumOperands() > 2) {
        // Taken counts for true branch
        // auto& TrueBranchMD = BrWeightMD->getOperand(1);
        // Taken counts for false branch
        // auto& FalseBranchMD = BrWeightMD->getOperand(2);
        // errs() << TrueBranchMD << ", " << FalseBranchMD << "\n";
      // }
    //   errs() << "I saw a block called " << B.getName() << "\n";
    //   for (auto &I : B) {
    //     errs() << I << "\n";
    //   }
    }
    return false;
  }
};
} // namespace

char DebugPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerDebugPass(const PassManagerBuilder &,
                                 legacy::PassManagerBase &PM) {
  PM.add(new DebugPass());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerDebugPass);
