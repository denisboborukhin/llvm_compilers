#include <iostream>

extern "C" void dumpInstr(const char *InstrName, const char *op1, const char *op2) {
    std::cout << InstrName << " <- " << op1 << ", " << op2 << '\n';
}