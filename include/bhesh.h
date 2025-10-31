#ifndef BHESH_H
#define BHESH_H

// Includes "datastructs.h" from bhesh/include
#include "datastructs.h"

/*
    Declares function: Shell_init with struct Shell 
    as arguments from datastructs.h -> Shell

    Usage: For initializing Shell data
*/
int Shell_init(Shell *self);

/*
    Declares function: Shell_cleanup with struct Shell 
    as arguments from datastructs.h -> Shell

    Usage: For cleaning up memory allocated data 
*/
void Shell_cleanup(Shell *self);

/*
    Declares function: Shell_loop with struct Shell 
    as arguments from datastructs.h -> Shell

    Usage: For keeping the program running
*/
int Shell_loop(Shell * self);

#endif