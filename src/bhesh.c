
// C Libraries
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

// Included Headers
#include "bhesh.h"
#include "prompt.h"
#include "input.h"
#include "constants.h"

// Function: Shell_init
int Shell_init(Shell *self)
{

// Fetches homepath directory
#if defined(_WIN32) || defined(_WIN64)
    self->home_dir = getenv("HOMEDRIVE");
#elif defined(__linux__) || defined(__APPLE__) && defined(__MACH__)
    self->home_dir = getenv("HOME");
#else
    // if OS is unknown bhesh may not work properly unless modified
    perror("Unknown operating system!\n");
    return 1;

#endif

    chdir(&*self->home_dir);

    // Print interface initially
    if (!printInterface(SHELL_INDICATOR, self, C_1, C_2))
            return 1;

    return 0;
}

// Function: Shell_loop
int Shell_loop(Shell *self) 
{
    size_t curr_command_size = 64 * sizeof(char); 

    /* Allocates a space for command data and
     stores it to the struct Shell -> string commands */
    self->commands = malloc(curr_command_size);
    
    if (self->commands == NULL)
    {
        perror("Failed to allocate self->commands (bhesh.c) ->");
        return 1;
    }

    // Initialize the allocated space by 0 for char as '\0'
    memset(self->commands, 0, curr_command_size);    

    // Starts the shell loop
    while (true)
    {
        /* 
            Fetch the shell user input and store it to self->commands,
            returns false if an error went wrong, else true if successful
        */
        if (!fetchInput(&self->commands, &curr_command_size))
            return 1;

        /* 
            Get shell user commands as: head (main command)
            and args (command arguments)
        */
        Command *cmds = getCommands(self);

        if (cmds == NULL)
            return 1;

        // Updates shell interface aftter command execution
        if (!printInterface(SHELL_INDICATOR, self, C_1, C_2))
            return 1;
    }

    return 0;
}

// Function: Shell_cleanup
void Shell_cleanup(Shell *self)
{
    // Free the memory allocated data
    free(self->commands);
}