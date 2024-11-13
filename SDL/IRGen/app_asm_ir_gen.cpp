#include "sim.h"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace llvm;

const int REG_FILE_SIZE = 16;
uint32_t REG_FILE[REG_FILE_SIZE] = {};

#ifdef CALL_FUNCS
void do_ADD(int dst, int src1, int src2) {
    REG_FILE[dst] = REG_FILE[src1] + REG_FILE[src2];
}
void do_SUB(int dst, int src1, int src2) {
    REG_FILE[dst] = REG_FILE[src1] - REG_FILE[src2];
}
void do_MUL(int dst, int src1, int src2) {
    REG_FILE[dst] = REG_FILE[src1] * REG_FILE[src2];
}

void do_MOD(int dst, int src, int mod) { REG_FILE[dst] = REG_FILE[src] % mod; }
void do_MOV(int dst, int value) { REG_FILE[dst] = value; }

void do_CMP(int reg1, int reg2) {
    REG_FILE[REG_FILE_SIZE - 1] = (REG_FILE[reg1] == REG_FILE[reg2]) ? 1 : 0;
}
// void do_JP(int& pc, int targetIndex) { pc = targetIndex; }
// void do_JZ(int& pc, int targetIndex) { if (REG_FILE[REG_FILE_SIZE - 1] == 0)
// { pc = targetIndex; } }

void do_SIM_PUT_PIXEL(int x, int y, int color) {
    std::cerr << "putPixel\n";
    simPutPixel(REG_FILE[x], REG_FILE[y], REG_FILE[color]);
}
void do_SIM_RAND(int reg) {
    std::cerr << "rand\n";
    REG_FILE[reg] = rand();
}
void do_SIM_FLUSH() { simFlush(); }
#endif

std::vector<std::string>
parseAsm(const std::string &filename,
         std::unordered_map<std::string, int> &labelMap,
         std::unordered_map<std::string, BasicBlock *> &BBMap,
         LLVMContext &context, Function *mainFunc) {
    std::ifstream input(filename);
    std::string line;

    if (!input.is_open()) {
        std::cerr << "[ERROR] Can't open file " << filename << "\n";
        exit(1);
    }

    std::vector<std::string> insnStream;
    while (getline(input, line)) {
        std::string insnLine;
        std::stringstream stream(line);

        while (stream) {
            std::string token;
            stream >> token;
            if (token.empty()) {
                continue;
            }

            if (token[0] == ';') {
                break;
            }

            if (token.back() == ':') {
                std::string name = token.substr(0, token.size() - 1);
                BBMap[name] = BasicBlock::Create(context, name, mainFunc);
                token = name;
            }

            if (token.back() == ',') {
                token = token.substr(0, token.size() - 1);
            }

            // if (!insnLine.empty()) {
            //     insnLine += " ";
            // }
            insnLine += " " + token;
        }

        if (!insnLine.empty()) {
            insnStream.push_back(insnLine);
        }
    }

    input.close();
    return insnStream;
}

#ifndef CALL_FUNCS
std::vector<int>
#else
std::vector<Value *>
#endif
parse3RegsArgs(std::stringstream &stream, IRBuilder<> &builder) {
    std::string arg1, arg2, arg3;
    stream >> arg1 >> arg2 >> arg3;
#ifndef CALL_FUNCS
    std::vector<int> res;
    res.push_back(std::stoi(arg1.substr(1)));
    res.push_back(std::stoi(arg2.substr(1)));
    res.push_back(std::stoi(arg3.substr(1)));
#else
    std::vector<Value *> res;
    res.push_back(builder.getInt32(std::stoi(arg1.substr(1))));
    res.push_back(builder.getInt32(std::stoi(arg2.substr(1))));
    res.push_back(builder.getInt32(std::stoi(arg3.substr(1))));
#endif
    return res;
}

#ifndef CALL_FUNCS
std::vector<int>
#else
std::vector<Value *>
#endif
parse2RegsArgs(std::stringstream &stream, IRBuilder<> &builder) {
    std::string arg1, arg2;
    stream >> arg1 >> arg2;
#ifndef CALL_FUNCS
    std::vector<int> res;
    res.push_back(std::stoi(arg1.substr(1)));
    res.push_back(std::stoi(arg2.substr(1)));
#else
    std::vector<Value *> res;
    res.push_back(builder.getInt32(std::stoi(arg1.substr(1))));
    res.push_back(builder.getInt32(std::stoi(arg2.substr(1))));
#endif
    return res;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        outs() << "[ERROR] Need 1 argument: file with assembler code\n";
        return 1;
    }

    LLVMContext context;
    Module *module = new Module("top", context);
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    IRBuilder<> builder(context);

    Type *int32Type = Type::getInt32Ty(context);

    ArrayType *regFileType =
        ArrayType::get(builder.getInt32Ty(), REG_FILE_SIZE);
    module->getOrInsertGlobal("regFile", regFileType);
    GlobalVariable *regFile = module->getNamedGlobal("regFile");

    // declare void @main()
    FunctionType *funcType = FunctionType::get(builder.getVoidTy(), false);
    Function *mainFunc =
        Function::Create(funcType, Function::ExternalLinkage, "main", module);

#ifdef CALL_FUNCS
    FunctionType *voidFuncType = FunctionType::get(builder.getVoidTy(), false);
    FunctionType *int32x3FuncType = FunctionType::get(
        builder.getVoidTy(),
        {builder.getInt32Ty(), builder.getInt32Ty(), builder.getInt32Ty()},
        false);
    FunctionType *int32x2FuncType =
        FunctionType::get(builder.getVoidTy(),
                          {builder.getInt32Ty(), builder.getInt32Ty()}, false);
    FunctionType *int32x1FuncType =
        FunctionType::get(builder.getVoidTy(), {builder.getInt32Ty()}, false);

    Function *do_ADD_Func = cast<Function>(
        module->getOrInsertFunction("do_ADD", int32x3FuncType).getCallee());
    Function *do_SUB_Func = cast<Function>(
        module->getOrInsertFunction("do_SUB", int32x3FuncType).getCallee());
    Function *do_MUL_Func = cast<Function>(
        module->getOrInsertFunction("do_MUL", int32x3FuncType).getCallee());

    Function *do_MOD_Func = cast<Function>(
        module->getOrInsertFunction("do_MOD", int32x3FuncType).getCallee());
    Function *do_MOV_Func = cast<Function>(
        module->getOrInsertFunction("do_MOV", int32x2FuncType).getCallee());

    Function *do_CMP_Func = cast<Function>(
        module->getOrInsertFunction("do_CMP", int32x2FuncType).getCallee());
    // Function *do_JP_Func =
    // cast<Function>(module->getOrInsertFunction("do_JP",
    // int32x2FuncType).getCallee()); Function *do_JZ_Func =
    // cast<Function>(module->getOrInsertFunction("do_JZ",
    // int32x2FuncType).getCallee());

    Function *do_SIM_PUT_PIXEL_Func = cast<Function>(
        module->getOrInsertFunction("do_SIM_PUT_PIXEL", int32x3FuncType)
            .getCallee());
    Function *do_SIM_RAND_Func = cast<Function>(
        module->getOrInsertFunction("do_SIM_RAND", int32x1FuncType)
            .getCallee());
    Function *do_SIM_FLUSH_Func = cast<Function>(
        module->getOrInsertFunction("do_SIM_FLUSH", voidFuncType).getCallee());

#else
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
    FunctionCallee simFlushFunc =
        module->getOrInsertFunction("simFlush", simFlushType);

    FunctionType *simRandType =
        FunctionType::get(Type::getInt32Ty(context), {}, false);
    FunctionCallee simRandFunc =
        module->getOrInsertFunction("simRand", simRandType);
#endif

    BasicBlock *BB0 = BasicBlock::Create(context, "", mainFunc);

    std::unordered_map<std::string, int> labelMap;
    std::unordered_map<std::string, BasicBlock *> BBMap;
    std::vector<std::string> insnuctions =
        parseAsm(argv[1], labelMap, BBMap, context, mainFunc);
#ifdef DEBUG
    for (auto insn : insnuctions) {
        std::cerr << insn << "\n";
    }
#endif
    builder.SetInsertPoint(BB0);
    Value *reg_0 = builder.CreateConstGEP2_32(regFileType, regFile, 0, 0);
    builder.CreateStore(builder.getInt32(0), reg_0);
    Value *reg_1 = builder.CreateConstGEP2_32(regFileType, regFile, 0, 1);
    builder.CreateStore(builder.getInt32(1), reg_1);

    BasicBlock *currBlock = BBMap["app"];
    builder.CreateBr(currBlock);

    builder.SetInsertPoint(currBlock);
    for (auto&& insnLine: insnuctions) {
        std::stringstream stream(insnLine);
        std::string opcode;
        stream >> opcode;
#ifdef DEBUG
        std::cerr << opcode << "\n";
#endif

        if (opcode == "SIM_RAND") {
            std::string arg1;
            stream >> arg1;
#ifndef CALL_FUNCS
            auto arg = std::stoi(arg1.substr(1));
            Value *res = builder.CreateCall(simRandFunc, {});
            Value *reg_p =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, arg);
            builder.CreateStore(res, reg_p);
#else
            Value *arg = builder.getInt32(std::stoi(arg1.substr(1)));
            builder.CreateCall(do_SIM_RAND_Func, {arg});
#endif
        } else if (opcode == "ADD") {
            const auto args = parse3RegsArgs(stream, builder);
#ifndef CALL_FUNCS
            Value *reg_1 =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[1]);
            Value *reg_2 =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[2]);

            Value *res =
                builder.CreateNSWAdd(builder.CreateLoad(int32Type, reg_1),
                                     builder.CreateLoad(int32Type, reg_2));
            Value *reg_p =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[0]);
            builder.CreateStore(res, reg_p);
#else
            builder.CreateCall(do_ADD_Func, args);
#endif
        } else if (opcode == "SUB") {
            const auto args = parse3RegsArgs(stream, builder);
#ifndef CALL_FUNCS
            Value *reg_1 =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[1]);
            Value *reg_2 =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[2]);

            Value *res =
                builder.CreateNSWSub(builder.CreateLoad(int32Type, reg_1),
                                     builder.CreateLoad(int32Type, reg_2));
            Value *reg_p =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[0]);
            builder.CreateStore(res, reg_p);
#else
            builder.CreateCall(do_SUB_Func, args);
#endif
        } else if (opcode == "MUL") {
            const auto args = parse3RegsArgs(stream, builder);
#ifndef CALL_FUNCS
            Value *reg_1 =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[1]);
            Value *reg_2 =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[2]);

            Value *res =
                builder.CreateNSWMul(builder.CreateLoad(int32Type, reg_1),
                                     builder.CreateLoad(int32Type, reg_2));
            Value *reg_p =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[0]);
            builder.CreateStore(res, reg_p);
#else
            builder.CreateCall(do_MUL_Func, args);
#endif
        } else if (opcode == "MOD") {
            std::string sarg1, sarg2, sarg3;
            stream >> sarg1 >> sarg2 >> sarg3;

#ifndef CALL_FUNCS
            int args[3];
            args[0] = std::stoi(sarg1.substr(1));
            args[1] = std::stoi(sarg2.substr(1));
            args[2] = std::stoi(sarg3);
            Value *reg_1 =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[1]);

            Value *mod =
                builder.CreateSRem(builder.CreateLoad(int32Type, reg_1),
                                   builder.getInt32(args[2]));
            Value *reg_p =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[0]);
            builder.CreateStore(mod, reg_p);
#else
            Value *args[3];
            args[0] = builder.getInt32(std::stoi(sarg1.substr(1)));
            args[1] = builder.getInt32(std::stoi(sarg2.substr(1)));
            args[2] = builder.getInt32(std::stoi(sarg3));
            builder.CreateCall(do_MOD_Func, args);
#endif
        } else if (opcode == "CMP") {
            const auto &args = parse2RegsArgs(stream, builder);

#ifndef CALL_FUNCS
            Value *reg_1 =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[0]);
            Value *reg_2 =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[1]);

            Value *cmp =
                builder.CreateICmpEQ(builder.CreateLoad(int32Type, reg_1),
                                     builder.CreateLoad(int32Type, reg_2));
            Value *extended = builder.CreateZExt(cmp, int32Type);
            Value *reg_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                      REG_FILE_SIZE - 1);
            builder.CreateStore(extended, reg_p);
#else
            builder.CreateCall(do_CMP_Func, args);
#endif
        } else if (opcode == "CMPL") {
            const auto &args = parse2RegsArgs(stream, builder);

#ifndef CALL_FUNCS
            Value *reg_1 =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[0]);
            Value *reg_2 =
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[1]);

            Value *cmp =
                builder.CreateICmpSLT(builder.CreateLoad(int32Type, reg_1),
                                     builder.CreateLoad(int32Type, reg_2));
            Value *extended = builder.CreateZExt(cmp, int32Type);
            Value *reg_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                      REG_FILE_SIZE - 1);
            builder.CreateStore(extended, reg_p);
#else
            builder.CreateCall(do_CMP_Func, args);
#endif
        } else if (opcode == "MOV") {
            std::string arg1, arg2;
            stream >> arg1 >> arg2;

#ifndef CALL_FUNCS
            Value *reg_p = builder.CreateConstGEP2_32(
                regFileType, regFile, 0, std::stoi(arg1.substr(1)));
            Value *val = builder.getInt32(std::stoi(arg2));
            builder.CreateStore(val, reg_p);
#else
            Value *args[2];
            args[0] = builder.getInt32(std::stoi(arg1.substr(1)));
            args[1] = builder.getInt32(std::stoi(arg2));
            builder.CreateCall(do_MOV_Func, args);
#endif
        } else if (opcode == "JP") {
#ifndef CALL_FUNCS
            std::string arg1;
            stream >> arg1;
            builder.CreateBr(BBMap[arg1]);
#else
            do_JP(pc, labelMap[arg1]);
            builder.SetInsertPoint(BBMap[arg1]);
            continue;
#endif
        } else if (opcode == "JZ") {
            std::string arg1, arg2;
            stream >> arg1 >> arg2;

#ifndef CALL_FUNCS
            Value *reg_p = builder.CreateConstGEP2_32(regFileType, regFile, 0,
                                                      REG_FILE_SIZE - 1);
            Value *reg_i1 = builder.CreateTrunc(
                builder.CreateLoad(builder.getInt32Ty(), reg_p),
                builder.getInt1Ty());
            builder.CreateCondBr(reg_i1, BBMap[arg1], BBMap[arg2]);
#else
            builder.SetInsertPoint(BBMap[arg2]);
            do_JZ(pc, labelMap[arg1]);
            builder.SetInsertPoint(BBMap[arg1]);
            continue;
#endif
        } else if (opcode == "SIM_PUT_PIXEL") {
            const auto args = parse3RegsArgs(stream, builder);
#ifndef CALL_FUNCS
            std::vector<Value *> vargs;
            vargs.push_back(builder.CreateLoad(
                int32Type,
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[0])));
            vargs.push_back(builder.CreateLoad(
                int32Type,
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[1])));
            vargs.push_back(builder.CreateLoad(
                int32Type,
                builder.CreateConstGEP2_32(regFileType, regFile, 0, args[2])));
            builder.CreateCall(simPutPixelFunc, vargs);
#else
            builder.CreateCall(do_SIM_PUT_PIXEL_Func, args);
#endif
        } else if (opcode == "SIM_FLUSH") {
#ifndef CALL_FUNCS
            builder.CreateCall(simFlushFunc);
#else
            builder.CreateCall(do_SIM_FLUSH_Func, {});
#endif
        } else {
            builder.SetInsertPoint(BBMap[opcode]);
        }
    }

    ExecutionEngine *ee =
        EngineBuilder(std::unique_ptr<Module>(module)).create();
    ee->InstallLazyFunctionCreator([=](const std::string &fnName) -> void * {
#ifdef CALL_FUNCS
        if (fnName == "do_MOD")
            return reinterpret_cast<void *>(do_MOD);
        if (fnName == "do_ADD")
            return reinterpret_cast<void *>(do_ADD);
        if (fnName == "do_SUB")
            return reinterpret_cast<void *>(do_SUB);
        if (fnName == "do_MUL")
            return reinterpret_cast<void *>(do_MUL);
        if (fnName == "do_MOV")
            return reinterpret_cast<void *>(do_MOV);
        if (fnName == "do_CMP")
            return reinterpret_cast<void *>(do_CMP);
        // if (fnName == "do_JP") return reinterpret_cast<void *>(do_JP);
        // if (fnName == "do_JZ") return reinterpret_cast<void *>(do_JZ);
        if (fnName == "do_SIM_PUT_PIXEL")
            return reinterpret_cast<void *>(do_SIM_PUT_PIXEL);
        if (fnName == "do_SIM_RAND")
            return reinterpret_cast<void *>(do_SIM_RAND);
        if (fnName == "do_SIM_FLUSH")
            return reinterpret_cast<void *>(do_SIM_FLUSH);
#else
        if (fnName == "simPutPixel") {
            return reinterpret_cast<void *>(simPutPixel);
        }
        if (fnName == "simFlush") {
            return reinterpret_cast<void *>(simFlush);
        }
        if (fnName == "simRand") {
            return reinterpret_cast<void *>(simRand);
        }
#endif
        return nullptr;
    });

    module->print(outs(), nullptr);
    verifyFunction(*mainFunc, &outs());

    ee->addGlobalMapping(regFile, (void *)REG_FILE);
    ee->finalizeObject();

    simInit();

    ArrayRef<GenericValue> noargs;
    ee->runFunction(mainFunc, noargs);

    simExit();

    return 0;
}