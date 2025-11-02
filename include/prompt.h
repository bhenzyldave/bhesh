#ifndef PROMPT_H
#define PROMPT_H

// Includes Header
#include "datastructs.h"

/*
    Declares function: printInterface with shell_indicator,
    struct Shell, c1 and c2 as arguments.

        - shell_indicator -> Represents the shell interface
        such as default: " >".
        
        - c1 and c2 -> Represents the shell interface
         covering as for instance:

            Format: c1 + ~ + c2 + shell_indicator

            As default:
                c1 = ' ' and c2 = ' '
                shell_indicator = '>'

        Thus, default Shell Interface: " ~ >"

    Usage: Updates the shell interface
*/
void printInterface(char * shell_indicator, Shell * shell, char c1, char c2);

/*
    Declares function: get_curr_dir with no arguments.
    Usage: Returns the string value of the memory allocated
    current directory where the shell is currently at.
    Warning: Value must be freed at hand.
*/
char * get_curr_dir();

#endif