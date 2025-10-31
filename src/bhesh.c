
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
int Shell_init(Shell *self) // Arguments: struct Shell pointer
{


#if defined(_WIN32) || defined(_WIN64) // If defined as a Window Platform, use ENV: HOMEDRIVER

    self->home_dir = getenv("HOMEDRIVER"); // Assigns the HOME path for Windows

    // Note: We use same "HOME" for Mac and Linux, Reason: UNIX Systems

#elif defined(__linux__) // if defined as Linux Platform, use ENV: HOME

    self->home_dir = getenv("HOME"); // Assigns the HOME path for Linux

#elif defined(__APPLE__) && define(__MACH__) // if defined as MAC OS Platform, use ENV: HOME

    self->home_dir = getenv("HOME"); // Assigns the HOME path for MacOS

#else

    // if OS is unknown bhesh may not work properly unless modified
    perror("Unknown operating system!\n");
    return 1;

#endif

    chdir(&*self->home_dir); // Sets the current directory as HOME path
    printInterface(SHELL_INDICATOR, self, C_1, C_2); // Initially display shell

    return 0; // Ends the initialization on function: Shell_init()
}

// Function: Shell_loop
int Shell_loop(Shell *self) // Argument: struct Shell pointer
{
    // Initially defines the current command size as 64 chars
    size_t curr_command_size = 64 * sizeof(char); 

    /* Allocates a space for command data and
     stores it to the struct Shell -> string commands */
    self->commands = malloc(curr_command_size);
    
    // Checks if the allocation failed
    if (self->commands == NULL)
    {
        // Prints the error and returns 1 for error
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
        bool fetchResult = fetchInput(&self->commands, &curr_command_size);

        // Checks for error, Returns 1 if there are any
        if (!fetchResult)
            return 1;

        /* 
            Get shell user commands as: target (main command)
            and args (command arguments)
        */
        Command *cmds = getCommands(self);

        /*
            Checks if result is NULL (Generally, Allocation issues),
            Returns 1 for error
        */
        if (cmds == NULL)
            return 1;

        // Updates shell interface aftter command execution
        printInterface(SHELL_INDICATOR, self, C_1, C_2);
    }

    return 0; // Ends Shell_loop function
}

// Function: Shell_cleanup
void Shell_cleanup(Shell *self) // Arguments: struct Shell pointer
{
    // Free the memory allocated data
    free(self->commands);
}