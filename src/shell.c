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

    // Initialize shell
    if (Shell_init(&shell))
        return 1;
    
    // Starts shell loop
    if (Shell_loop(&shell))
        return 1;
        
    // Cleans up shell
    Shell_cleanup(&shell);

    return 0; // End shell program
}