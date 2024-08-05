#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"

/*
Assembler::Assembler( int argc, char *argv[] )

NAME

    Assembler::Assembler - constructor for the Assembler class.

SYNOPSIS

    Assembler::Assembler( int argc, char *argv[] );

DESCRIPTION

    Constructor for the assembler. We are passing argc and argv to the file access constructor.


AUTHOR

    Emily Acosta

DATE

    12/12/2023

*/

Assembler::Assembler(int argc, char* argv[])
    : m_facc(argc, argv)
{
}

// Nothing else to do here at this point.

/*
Assembler::PassI()

NAME

    PassI - first pass through the code.

SYNOPSIS

    Assembler::PassI();

DESCRIPTION

    This function is the first pass for the Assembler. Establishing the location of the
    labels and constructs a symbol table using the SymbolTable class.


AUTHOR

    Emily Acosta

DATE

    12/12/2023

*/
vector<pair<int, string>> m_machinecode;

void Assembler::PassI()
{
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    while (true) {

        // Read the next line from the source file.
        string line;
        if (!m_facc.GetNextLine(line)) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }
        // Parse the line and get the instruction type.
        Instruction::InstructionType st = m_inst.ParseInstruction(line);

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
        if (st == Instruction::ST_End) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip other instruction types. We can do better/
        if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
        {
            continue;
        }
        // If the instruction has a label, record it and its location in the
        // symbol table.
        if (m_inst.isLabel()) {

            m_symtab.AddSymbol(m_inst.GetLabel(), loc);
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction(loc);
    }
}


/*
Assembler::PassII()

NAME

    PassII - second pass through the code.

SYNOPSIS

    void Assembler::PassII();

DESCRIPTION

    In Pass II, we use the symbol table from Pass I to translate the code into machine language.
    It involves instruction translation, error recording,
    and printing original and translated instructions.
    Errors are displayed if they occur.

RETURNS


AUTHOR

    Emily Acosta

DATE

    12/12/2023

*/

void Assembler::PassII()
{
    m_facc.rewind(); // so we can read from the top
    int loc = 0;
    bool is_end = false; // Flag to show that the code has hit the end statement
    Errors::InitErrorReporting();

    // Clearing the vector which will be put into the emulator
    m_machinecode.clear();

    // Print the header for the translation table output
    cout << setw(15) << left << "Location" << setw(15) << left << "Contents" << "Original Statement" << endl;

    // process each line of code.
    while (true) {
        string line;
        if (!m_facc.GetNextLine(line)) {

            if (is_end == true)
                break;

            string error = "(location " + to_string(loc) + ") missing end statement";
            Errors::RecordError(error);
            break;
        }

        if (is_end == true) {
            string error = "(location " + to_string(loc) + ") lines after end statement";
            Errors::RecordError(error);
            break;
        }

        pair<int, string>  translation = m_inst.TranslateInstruction(line, loc);

        // Set the is_end flag to true
        if (translation == pair<int, string>(0, "end"))
            is_end = true;

        else if (translation != pair<int, string>(0, "  "))
            m_machinecode.push_back(translation);

        // get the location of the next instruction.
        loc = m_inst.LocationNextInstruction(loc);
    }
    if (!Errors::Empty())
        Errors::DisplayErrors();

    cout << "Enter to continue...";
    cin.ignore();
}


/*
Assembler::RunEmulator()

NAME

    Assembler::RunEmulator - run the emulator on the translated code.

SYNOPSIS

    void Assembler::RunEmulator();

DESCRIPTION

    Runs the emulator with the translated code in Pass II. If errors are found, it stops. Else,
    it loads the translated instructions into the emulator's memory and runs it.
    Any errors during emulation are reported later.

RETURNS


AUTHOR

    Emily Acosta

DATE

    12/12/2023

*/
/**/
void Assembler::RunProgramInEmulator()
{
    // Stop emulation if errors are found
    if (!Errors::Empty()) {
        cout << "Errors were encountered during compilation...\nExiting emulation\n";
        return;
    }

    // Insert machine code into the emulator class and report errors.
    for (auto it = m_machinecode.begin(); it != m_machinecode.end(); ++it) {
        cout << "Current value: " << it->second << endl; // Debug line
        try {
            // Check if the string is not a valid integer and handle it accordingly
            if (it->second == "n/a") {
                cerr << "Skipping non-integer value: " << it->second << endl;
                continue; // Skip this iteration
            }

            bool insertion_check = m_emul.insertMemory(it->first, stoi(it->second));
            if (!insertion_check) {
                string error = "Error inserting " + to_string(it->first) + " " + it->second + " into memory";
                Errors::RecordError(error);
            }
        }
        catch (const std::invalid_argument& e) {
            cerr << "Invalid argument for stoi: " << it->second << endl;
            // Handle the exception, maybe continue with the next iteration
        }
    }

    // Run and report errors if encountered any.
    bool run_check = m_emul.runProgram();
    if (run_check == false) {
        string error = "Error running the emulator";
        Errors::RecordError(error);
    }

    // Display any errors.
    if (!Errors::Empty())
        Errors::DisplayErrors();

    cin.ignore();
}
