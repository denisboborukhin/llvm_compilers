#include "llvm/IR/IRBuilder.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

namespace {

struct TracerPass final : public PassInfoMixin<TracerPass> {
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &FAM) {
        StringRef LOGGER_NAME = "dumpInstr";

        LLVMContext &Ctx = M.getContext();
        IRBuilder<> builder(Ctx);

        Type *retType = Type::getVoidTy(Ctx);
        ArrayRef<Type *> funcStartParamTypes = {
            builder.getInt8Ty()->getPointerTo(),
            builder.getInt8Ty()->getPointerTo(),
            builder.getInt8Ty()->getPointerTo()};
        FunctionType *LoggerType = FunctionType::get(retType, funcStartParamTypes, false);
        FunctionCallee logFunc = M.getOrInsertFunction(LOGGER_NAME, LoggerType);

        for (auto &&F : M) {
            if (F.getName() == LOGGER_NAME) {
                continue;
            }
            for (auto &&B : F) {
                for (auto &&I : B) {
                    if (dyn_cast<PHINode>(&I) != nullptr) {
                        continue;
                    }
                    const int NUM_INSN = 3;
                    std::vector<Value*>args{};

                    builder.SetInsertPoint(&I);
                    Value* opcodeName = builder.CreateGlobalStringPtr(I.getOpcodeName());
                    args.push_back(opcodeName);

                    for (auto&& use: I.uses()) {
                        Instruction* pUseInstr = dyn_cast<Instruction>(use);
                        if (pUseInstr == nullptr) {
                            continue;
                        }
                        builder.SetInsertPoint(pUseInstr);
                        Value* useOpcodeName = builder.CreateGlobalStringPtr(pUseInstr->getOpcodeName());
                        args.push_back(useOpcodeName);
                        if (args.size() == NUM_INSN) {
                            break;
                        }
                    }
                    while (args.size() != NUM_INSN) {
                        args.push_back(ConstantPointerNull::get(builder.getInt8Ty()->getPointerTo()));
                    }
                    builder.CreateCall(logFunc, ArrayRef<Value*>{args});
                }
            }
        }

    return PreservedAnalyses::none();
    }

    static bool isRequired() { return true; }
};

} // unnamed namespace

/* When a plugin is loaded by the driver, it will call this entry point to
obtain information about this plugin and about how to register its passes.
*/
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  auto callback = [](PassBuilder &PB) {
    PB.registerOptimizerLastEPCallback(
        [](ModulePassManager &MPM, [[maybe_unused]] OptimizationLevel) {
          MPM.addPass(TracerPass{});
          return true;
        });
  };

  return {LLVM_PLUGIN_API_VERSION, "Instruction tracer", "0.0.1", callback};
}