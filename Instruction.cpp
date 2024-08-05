#include "stdafx.h"
#include "Instruction.h"
#include "Errors.h"
#include "SymTab.h"

/*

NAME

    Instruction::ParseInstruction

SYNOPSIS

    Instruction::InstructionType Instruction::ParseInstruction(string & a_buff);

DESCRIPTION

    This function identifies the instruction type for the current line.
    It helps Pass I in the Assembler class find labels, the origin, and the end
    statement. It doesn't check for errors.


*/
Instruction::InstructionType Instruction::ParseInstruction(string& a_buff)
{
    m_Label = "";
    m_OpCode = "";
    m_Operand = "";
    m_instruction = a_buff;
    m_parsed_inst.clear();
    m_parsed_inst.resize(0);

    // where the comment starts
    size_t strt = m_instruction.find(';');

    // Deletes the comment
    if (strt != string::npos)
        m_instruction = m_instruction.substr(0, strt);

    stringstream ss(m_instruction);
    string temp;
    while (ss >> temp)
        m_parsed_inst.push_back(temp);

    if (m_parsed_inst.empty())
        m_type = InstructionType(2); //comment or blank line

    // Instruction to halt
    else if (to_lower(m_parsed_inst[0]) == "halt")
        m_type = InstructionType(0); //assembly language instruction
    //origin
    else if (to_lower(m_parsed_inst[0]) == "org")
        m_type = InstructionType(1); //assembler instruction

    // to end
    else if (to_lower(m_parsed_inst[0]) == "end")
        m_type = InstructionType(3); //end instruction

    else if (m_parsed_inst.size() == 2)
        m_type = InstructionType(0); //asm language instruction

    else {
        m_Label = m_parsed_inst[0];

        if (m_parsed_inst[1] == "dc" || m_parsed_inst[1] == "DC" || m_parsed_inst[1] == "ds" || m_parsed_inst[1] == "DS")
            m_type = InstructionType(1);
        else
            m_type = InstructionType(0);
    }

    return m_type;
}



/*

NAME

    Instruction::TranslateInstruction - initializer for the FileAccess class.

SYNOPSIS

    pair<int, string> Instruction::TranslateInstruction(string & a_buff, int a_loc);

DESCRIPTION

    This function translates source code instructions into VC370 machine code
    and handles errors, reporting them when necessary.

*/

pair<int, string> Instruction::TranslateInstruction(string& a_buff, int a_loc)
{
    // Parse the line and get the instruction type.
    Instruction::InstructionType st = ParseInstruction(a_buff);

    // If the instruction has more that three words, it must be an error
    if (m_parsed_inst.size() > 3) {
        string error = "(location " + to_string(a_loc) + ") More than three field";
        Errors::RecordError(error);
    }

    // For InstructionType(0) -- assembly language instruction which returns the machine code equivalent
    if (st == InstructionType(0)) {
        string assem_code = ""; // To store the assembly language code for the given instruction
        int loc = 0; // To store the location
        switch (m_parsed_inst.size()) {
        case (1):
            m_OpCode = to_lower(m_parsed_inst[0]);
            // Check to see if the word has an OpCode
            if (OpCode(m_OpCode) != -1) {
                if (m_OpCode == "halt")
                    assem_code = "130000";
                // Halt is the only OpCode which goes without an operand. Either its "halt" or its an error
                else {
                    string error = "(location " + to_string(a_loc) + ") Missing operand";
                    Errors::RecordError(error);
                    assem_code = to_string(OpCode(m_OpCode)) + "????";
                    pad(assem_code, 6);
                }
            }
            // Report an error otherwise
            else {
                string error = "(location " + to_string(a_loc) + ") Bad Operation Command";
                Errors::RecordError(error);
                assem_code = "??????";
            }
            break;
        case(2):
            m_OpCode = m_parsed_inst[0];
            m_Operand = m_parsed_inst[1];
            if (OpCode(m_OpCode) != -1) {
                assem_code = to_string(OpCode(m_OpCode));
                pad(assem_code, 2);

                if (SymbolTable::LookupSymbol(m_Operand, loc)) {
                    assem_code += pad(to_string(loc), 4);
                }
                else {
                    string error = "(location " + to_string(a_loc) + ") Undefined Operand/Label";
                    Errors::RecordError(error);
                    assem_code += "????";
                }
            }
            else {
                string error = "(location " + to_string(a_loc) + ") Bad Operation Command";
                Errors::RecordError(error);
                assem_code = "??????";
            }
            break;
        case(3):
            m_Label = m_parsed_inst[0];
            m_OpCode = m_parsed_inst[1];
            m_Operand = m_parsed_inst[2];

            if (OpCode(m_OpCode) != -1) {
                assem_code = to_string(OpCode(m_OpCode));
                pad(assem_code, 2);

                if (SymbolTable::LookupSymbol(m_Operand, loc)) {
                    assem_code += pad(to_string(loc), 4);
                }
                else {
                    string error = "(location " + to_string(a_loc) + ") Undefined Operand/Label";
                    Errors::RecordError(error);
                    assem_code += "????";
                }
            }
            else {
                string error = "(location " + to_string(a_loc) + ") Bad Operation Command";
                Errors::RecordError(error);
                assem_code = "??????";
            }
            break;
        default:
            assem_code = "??????";
            break;
        }
        cout << setw(12) << left << a_loc << setw(12) << left << assem_code << a_buff << endl;
        return pair<int, string>(a_loc, assem_code);
    }


    if (st == InstructionType(1) && m_parsed_inst.size() >= 3 && (m_parsed_inst[1] == "dc" || m_parsed_inst[1] == "DC"))
        cout << setw(12) << left << a_loc << setw(12) << left << pad(m_parsed_inst[2], 6) << a_buff << endl;
    // For InstructionType(1) -- assembler instruction
    else if (st == InstructionType(1))
        cout << setw(12) << left << a_loc << setw(12) << left << "" << a_buff << endl;
    // For InstructionType(2) -- comment or blank line and InstructionType(3) -- end
    else
        cout << setw(24) << " " << a_buff << endl;

    // To indicate the end statement
    if (st == InstructionType(3))
        return pair<int, string>(0, "end");

    return pair<int, string>(0, "n/a");
}


/*


NAME

    Instruction::LocationNextInstruction - get location for next line of code.

SYNOPSIS

    int Instruction::LocationNextInstruction(int a_loc);
    a_loc    --> location for the current instruction for the VC370.

DESCRIPTION

    Computes the location for the next line of machine code based on the current instruction.



*/
int Instruction::LocationNextInstruction(int a_loc)
{
    if (m_type == InstructionType(2) || m_type == InstructionType(3))
        return a_loc;
    else if (m_type == InstructionType(1)) {
        stringstream ss(m_instruction);
        string one, two, three;
        ss >> one >> two >> three;
        if (one == "org" || one == "ORG")
            return stoi(two);
        else if (two == "ds" || two == "DS")
            return a_loc + stoi(three);
    }

    return a_loc + 1;
}


/*
Instruction::to_lower(string &a_buff)

NAME

    Instruction::to_lower - return lowercase of input.

SYNOPSIS

    string Instruction::to_lower(string &a_buff);

DESCRIPTION

    Turns the input string to lowercase a creates a lowercase copy of the string.


*/
string Instruction::to_lower(string& a_buff)
{
    for (int i = 0; i < a_buff.size(); i++)
        a_buff[i] = tolower(a_buff[i]);
    return a_buff;
}



/*
Instruction::OpCode(string &a_buff)

NAME

    Instruction::OpCode

SYNOPSIS

    int Instruction::OpCode(string &a_buff);

DESCRIPTION

    Function returns the proper OpCode for the operation.


*/

int Instruction::OpCode(string& a_buff)
{
    // opcode instructions
    map<string, int> OpCode{
         { "add", 1 },{ "sub", 2 },{ "mult", 3 },{ "div", 4 },{ "load", 5 },
         { "store", 6 },{ "read", 7 },{ "write", 8 },{ "b", 9 },{ "bm", 10 },
         { "bz", 11 },{ "bp", 12 },{ "halt", 13 }
    };

    if (OpCode[a_buff] <= 13 && OpCode[a_buff] >= 1)
        return OpCode[a_buff];

    return -1;
}


/*
Instruction::pad(string &a_buff, int a_size)

NAME

    Instruction::pad

SYNOPSIS

    string Instruction::pad(string &a_buff, int a_size);

DESCRIPTION

    Function pads a string by adding 0's at the beginning until it's the desired size.


*/

string Instruction::pad(const string& a_buff, int a_size) {
    string result = a_buff;
    while (result.size() < static_cast<size_t>(a_size)) {
        result.insert(0, "0");
    }
    return result;
}