#ifndef _ERRORS_H
#define _ERRORS_H

/*
Errors Class

NAME

     Errors

DESCRIPTION

     Class used to manage errors and uses static variables to make them accessible everywhere.

AUTHOR

     Emily Acosta

DATE

     12/12/2023

*/



#include <string>
#include <vector>

class Errors {

public:

    // Initializes error reports.
    static void InitErrorReporting();

    // Records an error message.
    static void RecordError(string& a_emsg);

    // Displays the collected error message.
    static void DisplayErrors();

    // Check if the error list is empty.
    static bool Empty();

private:


};
#endif