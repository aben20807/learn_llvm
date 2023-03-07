#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
struct SkeletonPass : public FunctionPass {
  static char ID;
  SkeletonPass() : FunctionPass(ID) {}

  virtual bool runOnFunction(Function &F) {
    errs() << "I saw a function called '" << F.getName()
           << "', arg_size: " << F.arg_size() << "\n";

    SmallVector<std::pair<unsigned, MDNode *>, 4> MDs;
    F.getAllMetadata(MDs);
    for (auto &MD : MDs) {
      if (MDNode *N = MD.second) {
        errs() << *N << "\n";
        if (const auto *subProgram = dyn_cast<DISubprogram>(N)) {
          errs() << "func name: " << subProgram->getName() << "\n";
          errs() << "src line:  " << subProgram->getLine() << "\n";
          errs() << "src file:  " << subProgram->getFilename() << "\n";
          // errs() << subProgram->getDirectory() << "\n";
        } 
      }
    }

    // for (auto &B : F) {
    //   errs() << "I saw a block called " << B.getName() << "\n";
    //   for (auto &I : B) {
    //     errs() << I << "\n";
    //   }
    // }
    return false;
  }
};
} // namespace

char SkeletonPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                                 legacy::PassManagerBase &PM) {
  PM.add(new SkeletonPass());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerSkeletonPass);
