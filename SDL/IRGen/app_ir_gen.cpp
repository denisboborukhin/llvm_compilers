#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Attributes.h"

#include "sim.h"

using namespace llvm;

int main() {
    LLVMContext context;
    // ; ModuleID = 'app.c'
    // source_filename = "app.c"
    Module *module = new Module("app.c", context);
    IRBuilder<> builder(context);

    // declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef)
    // local_unnamed_addr #1
    Type *voidType = Type::getVoidTy(context);
    ArrayRef<Type *> simPutPixelParamTypes = {Type::getInt32Ty(context),
                                              Type::getInt32Ty(context),
                                              Type::getInt32Ty(context)};
    FunctionType *simPutPixelType =
        FunctionType::get(voidType, simPutPixelParamTypes, false);
    FunctionCallee simPutPixelFunc =
        module->getOrInsertFunction("simPutPixel", simPutPixelType);

    // declare void @simFlush(...) local_unnamed_addr #1
    FunctionType *simFlushType = FunctionType::get(voidType, {}, false);
    FunctionCallee simFlushFunc = module->getOrInsertFunction("simFlush", simFlushType);

    FunctionType *simRandType =
        FunctionType::get(Type::getInt32Ty(context), {}, false);
    FunctionCallee simRandFunc =
        module->getOrInsertFunction("simRand", simRandType);

    // define dso_local void @app() local_unnamed_addr #0 {
    FunctionType *appFuncType = FunctionType::get(builder.getInt32Ty(), false);
    Function *appFunc =
        Function::Create(appFuncType, Function::ExternalLinkage, "app", module);

    BasicBlock *BB0 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB1 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB23 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB25 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB29 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB32 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB37 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB39 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB42 = BasicBlock::Create(context, "", appFunc);

    builder.SetInsertPoint(BB0);
        builder.CreateBr(BB1);

    builder.SetInsertPoint(BB1);
        Value *app_val2 = builder.CreateCall(simRandFunc, {});
        Value *app_val3 = builder.CreateSRem(app_val2, builder.getInt32(492));
        Value *app_val4 = builder.CreateNSWAdd(app_val3, builder.getInt32(10));
        Value *app_val5 = builder.CreateCall(simRandFunc, {});
        Value *app_val6 = builder.CreateSRem(app_val5, builder.getInt32(236));
        Value *app_val7 = builder.CreateNSWAdd(app_val6, builder.getInt32(10));
        Value *app_val8 = builder.CreateCall(simRandFunc, {});
        Value *app_val9 = builder.CreateNSWSub(builder.getInt32(502), app_val3);
        Value *app_val10 = builder.CreateICmpSLT(app_val9, app_val4);
        Value *app_val11 = builder.CreateSelect(app_val10, app_val9, app_val4);
        Value *app_val12 = builder.CreateICmpSGT(app_val11, app_val7);
        Value *app_val13 = builder.CreateSelect(app_val12, app_val7, app_val11);
        Value *app_val14 = builder.CreateNSWSub(builder.getInt32(246), app_val6);
        Value *app_val15 = builder.CreateICmpSLT(app_val14, app_val13);
        Value *app_val16 = builder.CreateSelect(app_val15, app_val14, app_val13);
        Value *app_val17 = builder.CreateCall(simRandFunc, {}, "");
        Value *app_val18 = builder.CreateNSWAdd(app_val16, builder.getInt32(-9));
        Value *app_val19 = builder.CreateSRem(app_val17, app_val18);
        Value *app_val20 = builder.CreateNSWAdd(app_val19, builder.getInt32(2));
        Value *app_val21 = builder.CreateNSWSub(builder.getInt32(-2), app_val19);
        Value *app_val22 = builder.CreateICmpSLT(app_val19, builder.getInt32(-2));
        builder.CreateCondBr(app_val22, BB42, BB23);

    builder.SetInsertPoint(BB23);
        Value *app_val24 = builder.CreateNSWMul(app_val20, app_val20);
        builder.CreateBr(BB25);

    builder.SetInsertPoint(BB25);
        PHINode *app_val26 = builder.CreatePHI(builder.getInt32Ty(), 2);
        app_val26->addIncoming(app_val21, BB23);
        Value *app_val27 = builder.CreateNSWMul(app_val26, app_val26);
        Value *app_val28 = builder.CreateNSWAdd(app_val26, app_val4);
        builder.CreateBr(BB32);

    builder.SetInsertPoint(BB29);
        Value *app_val30 = builder.CreateAdd(app_val26, builder.getInt32(1));
        Value *app_val31 = builder.CreateICmpEQ(app_val26, app_val20);
        builder.CreateCondBr(app_val31, BB42, BB25);

    builder.SetInsertPoint(BB32);
        PHINode *app_val33 = builder.CreatePHI(builder.getInt32Ty(), 2);
        app_val33->addIncoming(app_val21, BB25);
        Value *app_val34 = builder.CreateNSWMul(app_val33, app_val33);
        Value *app_val35 = builder.CreateNSWAdd(app_val34, app_val27);
        Value *app_val36 = builder.CreateICmpUGT(app_val35, app_val24);
        builder.CreateCondBr(app_val36, BB39, BB37);

    builder.SetInsertPoint(BB37);
        Value *app_val38 = builder.CreateNSWAdd(app_val33, app_val7);
        Value *bb37Args[] = {app_val28, app_val38, app_val8};
        builder.CreateCall(simPutPixelFunc, bb37Args);
        builder.CreateBr(BB39);

    builder.SetInsertPoint(BB39);
        Value *app_val40 = builder.CreateAdd(app_val33, builder.getInt32(1));
        Value *app_val41 = builder.CreateICmpEQ(app_val33, app_val20);
        builder.CreateCondBr(app_val41, BB29, BB32);

    builder.SetInsertPoint(BB42);
        builder.CreateCall(simFlushFunc);
        builder.CreateBr(BB1);

    app_val26->addIncoming(app_val30, BB29);
    app_val33->addIncoming(app_val40, BB39);

    // Dump LLVM IR
    module->print(outs(), nullptr);

    // LLVM IR Interpreter
    outs() << "[EE] Run\n";
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
    ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
        if (fnName == "simPutPixel") {
            return reinterpret_cast<void *>(simPutPixel);
        }
        if (fnName == "simFlush") {
            return reinterpret_cast<void *>(simFlush);
        }
        if (fnName == "simRand") {
            return reinterpret_cast<void *>(simRand);
        }
        return nullptr;
    });
    ee->finalizeObject();

    simInit();

    ArrayRef<GenericValue> noargs;
    GenericValue v = ee->runFunction(appFunc, noargs);
    outs() << "[EE] Result: " << v.IntVal << "\n";

    simExit();
    return EXIT_SUCCESS;
}