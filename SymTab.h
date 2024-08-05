#pragma once

/*
Symbol Table Class

NAME

     SymbolTable

DESCRIPTION

     The SymbolTable class keeps track of symbols found in the source code.
     It's created in the first pass and used in the second pass to find label
     values and search for symbols. We make the LookupSymbol method static
     so that it can be accessed from anywhere in the code.

AUTHOR

     Emily Acosta

DATE

     12/12/2023

*/


class SymbolTable {

public:
    // Get rid of constructor and destructor if you don't need them.
    SymbolTable() {};
    ~SymbolTable() {};

    const int multiplyDefinedSymbol = -999;

    // Add a new symbol to the symbol table.
    void AddSymbol(string& a_symbol, int a_loc);

    // Display the symbol table.
    void DisplaySymbolTable();

    // Lookup a symbol in the symbol table.
    static bool LookupSymbol(const string& a_symbol, int& a_loc);



private:

};