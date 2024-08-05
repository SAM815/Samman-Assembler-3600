//
//		Implementation of the symbol table class.
//
#include "stdafx.h"
#include "SymTab.h"


static map<string, int> m_symbolTable;
/*
  NAME

      AddSymbol - adds a new symbol to the symbol table.

  SYNOPSIS

      void AddSymbol( char *a_symbol, int a_loc );

  DESCRIPTION

      This function will place the symbol "a_symbol" and its location "a_loc"
      in the symbol table.
 */

void SymbolTable::AddSymbol(string& a_symbol, int a_loc)
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st = m_symbolTable.find(a_symbol);
    if (st != m_symbolTable.end()) {

        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}


/*
  NAME

      DisplaySymbolTable

  SYNOPSIS

      void DisplaySymbolTable();

  DESCRIPTION

      Prints out the symbol table;
 */
void SymbolTable::DisplaySymbolTable()
{
    cout << setw(15) << left << "Symbol #" << setw(15) << left << "Symbol" << setw(15) << left << "Location" << endl;
    int count = 0;
    for (map<string, int>::iterator it = m_symbolTable.begin(); it != m_symbolTable.end(); ++it) {
        cout << setw(15) << left << count++ << setw(15) << left << it->first << setw(15) << left << it->second << endl;
    }
    cout << "Enter to continue...";
    cin.ignore();
}

/*


NAME

    LookupSymbol

SYNOPSIS

    bool SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc);

DESCRIPTION

    This function will lookup a symbol in the symbol table and if it's found, store the location of the symbol in a_loc.

AUTHOR

    Emily Acosta

DATE

    12/15/2023

*/

bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc)
{
    map<string, int>::iterator it = m_symbolTable.find(a_symbol);
    if (it != m_symbolTable.end()) {
        a_loc = it->second;
        return true;
    }
    return false;
}