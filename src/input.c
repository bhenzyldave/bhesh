// Includes C Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

// Includes Header
#include "input.h"

// Function: fetchInput
// Arguments: double pointer char commands and pointer size_t cmd_size
bool fetchInput(char **commands, size_t *cmd_size)
{
    // Initializes char int value to zero
    int c = 0;

    // Initializes number of loops, starting zero
    int i = 0;

    // Loops over stdin and get shell user input starting at char [0]
    while ((c = getchar()) != '\n' && c != EOF) // Loop if not the end of input, else stop
    {
        // If number of loops exceeds number of chars allocated
        // Exception -1 of cmd_size for null terminator
        if (i >= (*cmd_size) - 1)
        {
            // Resizes allocated data from Shell_loop() -> self->commands
            // For extra chars by doubling its size
            char * tmp_commands = realloc(*commands, ((*cmd_size) *= 2));

            // Checks if reallocation failed
            if (tmp_commands == NULL)
            {
                // Prints error and return false for program failure
                perror("Failed to allocate commands (input.c) ->");
                return false;
            }

            // Safely store to self->commands
            *commands = tmp_commands;

            // Continue to check for further overflow
            continue;
        }

        // Assign block in [i] from stdin char 
        // And post-increment i
        (*commands)[i++] = (char)c; // Use of char conversion since c is an int of char
    }

    // If there's an input, assign the last reserved block for null terminator
    if (c != 0)
        (*commands)[i] = '\0';

    // Ends program and return true for success
    return true;
}

// -
void handleCommands(Command cmd)
{
}

// Function: getCommands
Command *getCommands(Shell *shell) // Arguments: struct Shell pointer
{
    // Declares new Command pointer and assign the
    // memory address of allocation with its respective size
    Command *cmds = malloc(sizeof(Command));

    // Checks if allocation was successful
    if (cmds == NULL)
    {
        // Print the error and return NULL for erorr
        perror("Failed to getCommandHead or getCommandBody (input.c) ->");
        return NULL;
    }

    // Initializes the new struct correspondingly
    cmds->args = NULL;
    cmds->args_size = 0;
    cmds->target = NULL;
    cmds->target_size = 0;

    // Calls getCommandHead and assigns to gT
    // For checking errors
    bool gT = getCommandHead(shell, cmds); // Get target command

    // Checks if there are any errors
    if (!gT)
    {
        // Prints error. free the allocated Command struct, 
        // and return NULL for error
        perror("Failed to getCommandHead (input.c) ->");
        free(cmds);
        return NULL;
    }

    printf("%s\n", (char *)cmds->target);
    printf("%d\n", cmds->target_size);

    // Calls getCommandBody and assigns to gA
    // For checking errors
    bool gA = getCommandBody(shell, cmds); // Get command arguments

    // Checks if there are any errors
    if (!gA)
    {
        // Prints error. free the allocated Command struct, 
        // and return NULL for error
        perror("Failed to getCommandBody (input.c) ->");
        free(cmds);
        return NULL;
    }

    if (cmds->args != NULL)
        printf("%s\n", cmds->args[0]);

    printf("%d\n", cmds->args_size);

    // End function and return new Struct
    return cmds;
}

// Function: getCommandHead
// Arguments: struct Shell pointer and struct cmd pointer
bool getCommandHead(Shell *shell, Command *cmd)
{
    // Assigns target_size as initially 64 chars
    int target_size = 64 * sizeof(char);
    
    // Allocates initial target and assign to Command
    cmd->target = malloc(target_size);

    // Checks if the allocation failed
    if (cmd->target == NULL)
    {
        // Prints error and return false for failure
        perror("Failed to allocate cmd->target (input.c) ->");
        return false;
    }
    
    // Placeholder if a letter is found 
    // to deal with >___command where _ are whitespaces
    bool letterFound = false;

    // Initializes number of loops
    int i = 0;

    // Initilizes current char location
    // On shell->commands shell user input
    int j = 0;

    // Starts loop
    while (true)
    {
        //  Assigns current character
        char c = shell->commands[j];

        // If end of shell user input data
        if (c == '\0' || c == '\n' || c == ' ' || !c)
        {
            /// If end is whitespace and letter is not yet found
            if (c == ' ' && !letterFound)
            {
                j++; // Increment j as for next char
                continue; // Skips current loop to avoid allocating whitespaces
            }

            // Else break (end of target)
            break;
        }

        // If number of loops exceeds allocated size
        if (i >= target_size - 1)
        {
            // Safely reallocates new size by doubling space for new chars
            char * tmp_target = realloc(cmd->target, sizeof(char) * (target_size *= 2));

            // Checks if allocation failed
            if (tmp_target == NULL)
            {
                // Print serror, free the allocated atrget, and return false for error
                perror("Failed to re-allocate cmd->target (input.c) ->");
                free(cmd->target);
                return false;
            }

            // Assigns allocated space address to main variable
            cmd->target = tmp_target;
            continue; // Skip sfor possible overflow checking
        }

        cmd->target[i++] = c; // Assigns char space to current character
        letterFound = true; // Assigns true for letter is found proof after endline checks
        j++; // Increments for next character
    }

    // Assign last reserved space for null terminal
    cmd->target[i] = '\0';

    // Assign j as target size with additional pre-increment as j starts from 0
    cmd->target_size = ++j;

    return true; // Ends function, return true for success
}

// Function: getCommandBody
// Arguments: struct Shell pointer and struct Command pointer
bool getCommandBody(Shell *shell, Command *cmd)
{
    // Initializes current c with target size to skip target
    int curr_c = cmd->target_size;
    // Declares function variable current char of input
    char tmp_c = shell->commands[curr_c];

    // If char is end, return true for successful
    // Result: command had no argument
    if (tmp_c == '\n' || tmp_c == '\0' || !tmp_c)
        return true;

    // Starts from 1 arg (assumption)
    int argsSize = 1;

    // Allocates space for first arg
    cmd->args = malloc(sizeof(char *) * argsSize);

    // Assigns number of loops
    int i = 0;

    // Starts loop for arg list
    while (true)
    {
        // Updates current char for i > 0 for current arg
        tmp_c = shell->commands[curr_c];

        // If whitespace
        if (tmp_c == ' ')
        {
            // Skips for next argument
            curr_c++;
            continue;
        }

        // If end of command, break (no args left)
        if (tmp_c == '\n' || tmp_c == '\0' || !tmp_c)
            break;

        // If numeber of loops is equal to argsSize
        if (i == argsSize)
        {
            // Safely resizes allocated arg by +1 (Add new arg to the array)
            char ** tmp_args = realloc(cmd->args, (++argsSize) * sizeof(char *));

            // Checks if allocation was successful
            if (tmp_args == NULL)
            {
                // Prints error
                perror("Failed to re-allocate cmd->args (input.c) ->");

                // Cleans

                return false;
            }

            // If successful, assigns to main variable the new memory allocated space
            cmd->args = tmp_args;
        }

        // Assigns current arg string size 32 chars and allocate
        int tmp_size = 32 * sizeof(char);
        char *tmp = malloc(tmp_size);

        // Checks if allocation was successful
        if (tmp == NULL)
        {
            // Prints error
            perror("Failed to allocate tmp (input.c) ->");

            // Clean

            return false;
        }

        // Assigns number of loops for strings
        int j = 0;

        // Starts loop for args list string chars
        while (true)
        {
            // If number of loops exceeds allocated size
            if (j >= tmp_size - 1)
            {
                // Doubles allocation size and store safely
                char * tmp_tmp = realloc(tmp, sizeof(char) * (tmp_size *= 2));

                // Checks if allocation succeeded
                if (tmp_tmp == NULL)
                {
                    // Prints error
                    perror("Failed to re-allocate tmp (input.c) ->");

                    // Clean

                    return false;
                }

                // Replaces main to new allocated address
                tmp = tmp_tmp;
                continue; // Skips for possible overflow checks
            }

            // Update current char with post-increment for next char
            tmp_c = shell->commands[curr_c++];

            // If char is end break loop for new arg
            if (tmp_c == '\n' || tmp_c == ' ' || tmp_c == '\0' || !tmp_c)
                break;

            // Else, assign current char to current arg block
            tmp[j++] = tmp_c;
        }

        // Assign last block reserved for null terminator
        tmp[j] = '\0';

        // Assign string to arg number i
        cmd->args[i++] = tmp;
    }

    // Assign args_size
    cmd->args_size = argsSize;
    return true; // Ends function, returns true for successful
}

// Function: isShellCommand
// Argument: target string
bool isShellCommand(char *target)
{
    // Maintainer Note: Add more commands later

    // Initializes built-in shell commands
    char *shellCmdTargets[] = {
        "cd", "pwd", "export", "exit"};

    // Explicitly state the number of shell commands for performance reasons
    // Where number of strings on shellCmdTargets - 1 is on i < n
    for (int i = 0; i < 3; i++)
    {
        // If it matches command, return true
        if (strcmp(shellCmdTargets[i], target) == 0)
            return true;
    }

    // Return false for no match on commands
    return false;
}