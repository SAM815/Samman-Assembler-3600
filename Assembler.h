#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"


class Assembler {

public:
    Assembler(int argc, char* argv[]);

    // Pass I - establish the locations of the symbols
    void PassI();

    // Pass II - generate a translation
    void PassII();

    // Display the symbols in the symbol table.
    void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }

    // Run emulator on the translation.
    void RunProgramInEmulator();

private:

    FileAccess m_facc;	    // File Access object
    SymbolTable m_symtab;	// Symbol table object
    Instruction m_inst;	    // Instruction object
    emulator m_emul;        // Emulator object

};