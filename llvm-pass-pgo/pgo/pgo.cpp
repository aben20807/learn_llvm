#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Analysis/BranchProbabilityInfo.h"
#include "llvm/Analysis/BlockFrequencyInfo.h"

using namespace llvm;

namespace {
struct PGOPass : public FunctionPass {
  static char ID;
  PGOPass() : FunctionPass(ID) {}

  virtual bool runOnFunction(Function &F) override {
    errs() << "I saw a function called '" << F.getName()
           << "', arg_size: " << F.arg_size() << "\n";

    Function::ProfileCount EntryCount = F.getEntryCount();
    if (EntryCount.hasValue()) {
      uint64_t EntryCountVal = EntryCount.getCount();
      errs() << "ProfileCount: " << EntryCountVal << "\n";
    }

    // Ref: https://opensource.apple.com/source/clang/clang-703.0.29/src/lib/Transforms/Vectorize/LoopVectorize.cpp.auto.html
    BlockFrequencyInfo* BFI = &getAnalysis<BlockFrequencyInfoWrapperPass>().getBFI();
    // Ref: https://github.com/microsoft/llvm-1/blob/d91b01bb7602ac9a89e3e352a5e464eeefb3ed08/unittests/Analysis/BlockFrequencyInfoTest.cpp#L79
    auto BB0Freq = BFI->getEntryFreq();
    // errs() << "BB0Freq: " << BB0Freq << "\n";

    for (auto& B : F) {
      errs() << "I saw a block called " << B.getName() << "\n";
      auto BB1Freq = BFI->getBlockFreq(&B).getFrequency();
      errs() << "Freq: " << BB1Freq/BB0Freq << "\n";
      auto BB1Freq_profile = BFI->getBlockProfileCount(&B);
      errs() << "Freq (profile): " << BB1Freq_profile << "\n\n";
    }
    return false;
  }

  void getAnalysisUsage(AnalysisUsage &AU) const override {
    // Ref: https://opensource.apple.com/source/clang/clang-703.0.29/src/lib/Transforms/Vectorize/LoopVectorize.cpp.auto.html
    AU.addRequired<BlockFrequencyInfoWrapperPass>();
  }
};
} // namespace

char PGOPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerPGOPass(const PassManagerBuilder &,
                            legacy::PassManagerBase &PM) {
  PM.add(new PGOPass());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerPGOPass);
