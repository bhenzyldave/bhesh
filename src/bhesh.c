
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
#include "shell_exec.h"

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

    // Set the directory and print interface initially
    return (!chdir(&*self->home_dir)) && printInterface(SHELL_INDICATOR, self, C_1, C_2);
}

// Function: Shell_run
int Shell_run(Shell *self)
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

    bool errno = false;

    // Starts the shell loop
    while (!errno)
    {

        Command *cmds = malloc(sizeof(Command));

        if (cmds == NULL)
        {
            perror("Failed to getCommandHead or getCommandBody (input.c) ->");
            return 1;
        }

        cmds->body = NULL;
        cmds->body_size = 0;
        cmds->head = NULL;
        cmds->head_length = 0;

        /*
            Fetch the shell user input and store it to self->commands,
            returns false if an error went wrong, else true if successful
        */
        if (!fetchInput(&self->commands, &curr_command_size))
        {
            errno = true;
            break;
        }

        /*
            getCommands(): Get shell user commands as: head (main command)
            and body (command arguments)
        */

        // Execute processed chronologically and check once
        if (!getCommands(self, cmds) || !manageCommands(cmds)    // Execute the commands
            || !printInterface(SHELL_INDICATOR, self, C_1, C_2)) // Updates the shell interface
        {
            errno = true;
        }

        // Clean up allocated commands
        for (int n = 0; n < cmds->body_size; n++)
        {
            free(cmds->body[n]);
        }
        free(cmds->head);
        free(cmds->body);
        free(cmds);
    }

    // Clean and exit
    free(self->commands);
    return errno;
}