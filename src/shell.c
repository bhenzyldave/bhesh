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

    shell.commands = NULL;
    shell.exports = NULL;
    shell.exports_size = 0;
    shell.home_dir = NULL;

    // Initialize shell and run
    if (!Shell_init(&shell) || !Shell_run(&shell))
        return 1;

    return 0;
}