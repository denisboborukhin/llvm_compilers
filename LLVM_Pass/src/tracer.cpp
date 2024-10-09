#include <iostream>

extern "C" void dumpInstr(const char* InstrName, const char* op1, const char* op2) {
    std::cout << InstrName;
    if (op1 != nullptr) {
        std::cout << " <- " << op1;
    }
    if (op2 != nullptr) {
        std::cout << ", " << op2;
    }
    std::cout << '\n';
}