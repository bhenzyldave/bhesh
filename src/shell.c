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
    // New Shell
    Shell shell;

    // Initialize shell
    int r1 = Shell_init(&shell);

    // Checks if error occurred
    if (r1) return 1;
    
    // Starts shell loop
    Shell_loop(&shell);

    // Cleans up shell
    Shell_cleanup(&shell);

    return 0; // End shell program
}