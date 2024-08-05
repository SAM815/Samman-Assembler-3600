//
//      Implementation of the Errors class.
//
#include "stdafx.h"
#include "Errors.h"

static vector<string> m_ErrorMsgs;

/*
Errors::InitErrorReporting()

NAME

    Errors::InitErrorReporting

SYNOPSIS

    void Errors::InitErrorReporting();

DESCRIPTION

    Initializing the class that will report errors by clearing the vector that stores all the errors.

RETURNS


AUTHOR

    Emily Acosta

DATE

    12/15/2023

*/

void Errors::InitErrorReporting()
{
    m_ErrorMsgs.clear();
}


/*
Errors::RecordError(string & a_emsg)

NAME

    Errors::RecordError

SYNOPSIS

    void Errors::RecordError(string & a_emsg);

DESCRIPTION

    Function records errors into a vector so they can be used to keep a log of the errors.

RETURNS


AUTHOR

    Emily Acosta

DATE

    12/15/2023

*/
void Errors::RecordError(string& a_emsg)
{
    m_ErrorMsgs.push_back(a_emsg);
}


/*
Errors::DisplayErrors()

NAME

    Errors::DisplayErrors

SYNOPSIS

    void Errors::DisplayErrors();

DESCRIPTION

    Prints out all the errors recorded with a number at the
    beginning of each line indicating that particular error.

AUTHOR

    Emily Acosta

DATE

    12/15/2023

*/

void Errors::DisplayErrors()
{
    int count = 0;
    for (vector<string>::iterator it = m_ErrorMsgs.begin(); it != m_ErrorMsgs.end(); ++it) {
        cout << "!ERROR " << setw(2) << count++ << "! " << *it << endl;
    }
}



/*
bool Errors::Empty()

NAME

    Errors::Empty

SYNOPSIS

    bool Errors::Empty();

DESCRIPTION

    To check for errors, we look at the size of the error vector.
    If the size is zero, there are no errors. Else if it's greater than zero,
    errors have been reported.


AUTHOR

    Emily Acosta

DATE

    12/15/2023

*/

bool Errors::Empty()
{
    return (m_ErrorMsgs.size() == 0) ? true : false;
}