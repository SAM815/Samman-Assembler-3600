# VC3600-Assembler


Project contains an assembler and emulator for VC3600 decimal computer.

/*--------------------------------------------------------------------------------------------------------------------*/

Handout for VC3600 Assembly language:

Statement Format:

An assembly language statement consists of from one to three fields.  These are:

Label - used to reference the statement.  It is optional.

Operation Code - a symbolic name for the number machine language op code.

Operand - Used to supply additional information.  For a machine language instruction this a label.

Labels start in column 1, all other fields separated by blanks or tabs.

Symbolic Operation Codes:
01 ADD        02 SUB     03 MULT     04 DIV     05 LOAD
06 STORE    07 READ  08 WRITE     09 B        10 BM
11 BZ           12 BP        13 HALT

Symbols: (I.e. labels and operands) are from 1 to 10 characters in length, the first of which is a letter and the remaining may be letters and digits.

Addresses:
An address my be specified by a label.

Assembler Language Instructions:

DC - define constant. The constant is a decimal integer placed in the operand field.

DS - define storage. The operand specifies the number of words of storage to be set aside.

ORG -define origin. The operand specifies the address at which the translation of the next instruction will be generated

END – indicates that there are no additional statements to translate.

Comments: 
Data after a ";" is a comment. Comments may appear anywhere within an instruction or by themselves. Blank lines are ignored.

Case Sensitivity:
All symbols will be case sensitive.  Operation codes may be written in upper or lower case or some combination of the two.

Example: 
The following is an assembler language program which will read in a number "n" and then compute and print the value of n!.
 

                org 100
                read n
more        load n; This is a comment

;Here is a comment that sit on its own line.
                mult fac
                store fac
                load n
                sub one
                store n
                bp more
                write fac
                halt
n              ds 100; just to show that you code can handle big areas.
fac           dc 1
one          dc 1
test          dc 1234 ; show your program can handle big constants.
                end
                
/*---------------------------------------------------------------------------------------------------------*/

Handout for VC3600 Machine Language

The VC-3600 is a decimal computer with 10,000 words of memory. Each word consists of 6 decimal digits. There is an additional word of memory called the accumulator. The machine language instructions for the VC-3600 is of the following form:

                             |2 digits             | 4 digits             | 
                             |operation code | address portion|

A machine language program is a sequence of machine language instructions stored in memory. The computer executes a machine language program by obeying the commands specified by a sequence of instructions stored in successive memory locations. The first instruction of a program is assumed to be at location 100. The following are the machine language instructions for the VC-3600.

NAME           OP. CODE     MEANING

ADD                     01           ACC <-- c(ACC) + c(ADDR)   (The contents of the accumulator and of the memory location specified by the address portion of the instruction are added together. The result is placed in the accumulator.): 
SUBTRACT         02            ACC <-- c(ACC) - c(ADDR) 
MULTIPLY           03            ACC <-- c(ACC) * c(ADDR) 
DIVIDE                 04            ACC <-- c(ACC) / c(ADDR) 
LOAD                   05            ACC <-- c(ADDR) 
STORE                06            ADDR <-- c(ACC) 
READ                   07            A line is read and its first 6 digits are placed in the specified address. 
WRITE                 08            c(ADDR) is displayed 
BRANCH              09           go to ADDR for next instruction 
BRANCH MINUS 10            go to ADDR if c(ACC) < 0 
BRANCH ZERO   11           go to ADDR if c(ACC) = 0 
BRANCH POSITIVE 12       go to ADDR if c(ACC) > 0 
HALT                    13           terminate execution


/*----------------------------------------------------------------------------------*/
