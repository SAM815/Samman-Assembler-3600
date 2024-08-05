//
//      Implementation of the Emulator class.
//
#include "stdafx.h"
#include "Emulator.h"
#include "Errors.h"

/*

NAME

    runProgram

SYNOPSIS

    bool emulator::runProgram();

DESCRIPTION

    Execute the emulator using the code stored in its memory.
    Each instruction is parsed line by line to extract the opcode and operand, and then
    the corresponding function is called based on the opcode.


*/

bool emulator::runProgram()
{
    // Moving the pointer to point to the origin location
    m_loc = m_org;
    for (int i = 0; i < MEMSZ; i++) {
        m_OpCode = m_memory[m_loc] / 10000;
        m_operand = m_memory[m_loc] % 10000;

        // 0 means the line is either declaring storage or a constant
        if (m_OpCode == 0) {
            m_loc++;
            continue;
        }

        switch (m_OpCode) {
        case 1:
            add();
            break;
        case 2:
            sub();
            break;
        case 3:
            mult();
            break;
        case 4:
            div();
            break;
        case 5:
            load();
            break;
        case 6:
            store();
            break;
        case 7:
            read();
            break;
        case 8:
            write();
            break;
        case 9:
            b();
            break;
        case 10:
            bm();
            break;
        case 11:
            bz();
            break;
        case 12:
            bp();
            break;
        case 13:
            halt();
            break;
        }

        if (m_kill) {
            return true;
        }
    }
    // meaning there is a missing halt
    return false;
}
void emulator::add()
{
    m_accum += m_memory[m_operand];
    if (m_accum > 999999) {
        cout << "Overflow\n";
        return;
    }
    m_loc++;
}


void emulator::sub()
{
    m_accum -= m_memory[m_operand];
    if (m_accum < -999999) {
        cout << "Overflow\n";
        return;
    }
    m_loc++;
}


void emulator::mult()
{
    m_accum *= m_memory[m_operand];
    if (m_accum > 999999 || m_accum < -999999) {
        cout << "Overflow\n";
        return;
    }
    m_loc++;
}
void emulator::div()
{
    m_accum /= m_memory[m_operand];
    if (m_accum > 999999 || m_accum < -999999) {
        cout << "Overflow\n";
        return;
    }

    m_loc++;
}
void emulator::load()
{
    m_accum = m_memory[m_operand];
    m_loc++;
}
void emulator::store()
{
    m_memory[m_operand] = m_accum;
    m_loc++;
}
void emulator::read()
{
    string input;
    cout << "? ";
    cin >> input;

    char sign = 'z';
    if (input[0] == '-' || input[0] == '+') {
        sign = input[0];
        input = input.erase(0, 1);
    }

    // Cutting off any digits after the first 6
    if (input.size() > 6)
        input = input.substr(0, 6);

    for (int i = 0; i < input.size(); i++) {
        if (!isdigit(input[i])) {
            cout << "Input is not all digits\n";
            return;
        }
    }

    m_loc++;
}
void emulator::write()
{
    cout << m_memory[m_operand] << endl;
    m_loc++;
}
void emulator::b()
{
    m_loc = m_operand;
}
void emulator::bm()
{
    if (m_accum < 0)
        m_loc = m_operand;
    else
        m_loc++;
}

void emulator::bz()
{
    if (m_accum == 0)
        m_loc = m_operand;
    else
        m_loc++;
}
void emulator::bp()
{
    if (m_accum > 0)
        m_loc = m_operand;
    else
        m_loc++;
}
void emulator::halt()
{
    m_kill = true;
}