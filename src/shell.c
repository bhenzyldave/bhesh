// MAIN PROGRAM (CORE)

// Includes C Library
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

// Include shell header
#include "bhesh.h"

// MAIN
int main()
{
    Shell shell;

    // Initialize shell and run
    if (!Shell_init(&shell) || !Shell_run(&shell))
        return 1;

    return 0;
}