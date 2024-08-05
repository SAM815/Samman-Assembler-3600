#pragma once

/*
Instruction Class

NAME

     Instruction

DESCRIPTION

     Class to parse and provide information about instructions.

AUTHOR

     Emily Acosta

DATE

     12/12/2023

*/


class Instruction {

public:

    Instruction() { };
    ~Instruction() { };

    // Codes to indicate the type of instruction we are processing.  Why is this inside the
   // class?
    enum InstructionType {
        ST_MachineLanguage, // A machine language instruction.
        ST_AssemblerInstr,  // Assembler Language instruction.
        ST_Comment,          // Comment or blank line
        ST_End               // end instruction.
    };

    // Parse the Instruction.  VICVIC
    InstructionType ParseInstruction(string& a_buff);


    // Compute the location of the next instruction.
    int LocationNextInstruction(int a_loc);

    // To access the label
    string& GetLabel() {

        return m_Label;
    };
    // To determine if a label is blank.
    bool isLabel() {

        return !m_Label.empty();
    };
    // Translate the Instruction.
    pair<int, string> TranslateInstruction(string& a_buff, int a_loc);



private:

    // The elemements of a instruction
    string m_Label;        // The label.
    string m_OpCode;       // The symbolic op code.
    string m_Operand;      // The operand.


    string m_instruction;  // The original instruction.

    // Derived value
    InstructionType m_type; // The type of instruction.

    // vector for storing the parsed instruction
    vector<string> m_parsed_inst;

    // convert a string to lower case in case it is in upper case
    string to_lower(string& a_buff);

    // operation code
    int OpCode(string& a_buff);

    // Used for padding a string to a_size digits by adding 0s in the beginning
    string pad(const string& a_buff, int a_size);
};