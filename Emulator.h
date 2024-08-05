#ifndef _EMULATOR_H      // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H


/*
Emulator Class

NAME

     Emulator

DESCRIPTION

     Emulation of the VC370 program

AUTHOR

     Emily Acosta

DATE

     12/12/2023

*/



class emulator {

public:

    const static int MEMSZ = 10'000;	// The size of the memory of the VC370.
    emulator() {

        memset(m_memory, 0, MEMSZ * sizeof(int));
        m_accum = 0;

        m_org = 0;
        m_firstinst = true;
        m_kill = false;

    }

    // Records instructions and data into VC370 memory.
    bool insertMemory(int a_location, int a_contents)
    {
        if (a_location >= 0 && a_location < MEMSZ)
        {
            m_memory[a_location] = a_contents;
            return true;
        }
        else
        {
            cerr << "Grumble gumble - should not happen" << endl;
            return false;
        }
    }

    // Runs the VC370 program recorded in memory.
    bool runProgram();

    // functions for VC370
    void add();
    void sub();
    void mult();
    void div();
    void load();
    void store();
    void read();
    void write();
    void b();
    void bm();
    void bz();
    void bp();
    void halt();

private:


    int m_memory[MEMSZ];    // The memory of the VC370.  Would have to make it
    // a vector if it was much larger.
    int m_accum;		    	// The accumulator for the VC370

    bool m_firstinst;              // The incoming statement is the first line
    int m_org;                     // Used for storing the origin location for the program
    int m_loc;                     // Used for storing the current location
    int m_OpCode;                  // Used for storing the OpCode for the current statement
    int m_operand;                 // Used for storing the operand for current statement
    bool m_kill;                   // Kill switch to be used with Halt

};

#endif