// Includes C Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

// Includes Header
#include "input.h"

// Function: fetchInput
bool fetchInput(char **commands, size_t *cmd_size)
{
    int c = 0; // Current char int
    int i = 0; // NUmber of loops

    // Loops over stdin and get shell user input starting at char [0]
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Checks for buffer overflow and safely resizes it to match buffer size
        if (i >= (*cmd_size) - 1)
        {
            char * tmp_commands = realloc(*commands, ((*cmd_size) *= 2));

            if (tmp_commands == NULL)
            {
                perror("Failed to allocate commands (input.c) ->");
                return false;
            }

            *commands = tmp_commands;
        }

        (*commands)[i++] = (char)c;
    }

    // Adds null terminator at last block
    if (c != 0)
        (*commands)[i] = '\0';

    return true;
}

// -
void handleCommands(Command cmd)
{
}

// Function: getCommands
Command *getCommands(Shell *shell)
{
    Command *cmds = malloc(sizeof(Command));

    if (cmds == NULL)
    {
        perror("Failed to getCommandHead or getCommandBody (input.c) ->");
        return NULL;
    }

    // Initializes the new struct correspondingly
    cmds->args = NULL;
    cmds->args_size = 0;
    cmds->head = NULL;
    cmds->target_size = 0;

    // Get the command head (head)
    if (!getCommandHead(shell, cmds))
    {
        perror("Failed to getCommandHead (input.c) ->");
        free(cmds);
        return NULL;
    }

    // DEBUG
    printf("%s\n", (char *)cmds->head);
    printf("%d\n", cmds->target_size);

    // Get the command body (args)
    if (!getCommandBody(shell, cmds))
    {
        perror("Failed to getCommandBody (input.c) ->");
        free(cmds);
        return NULL;
    }

    // DEBUG
    if (cmds->args != NULL)
        printf("%s\n", cmds->args[0]);
    printf("%d\n", cmds->args_size);

    return cmds;
}

// Function: getCommandHead
bool getCommandHead(Shell *shell, Command *cmd)
{
    int target_size = 64 * sizeof(char);
    cmd->head = malloc(target_size);

    if (cmd->head == NULL)
    {
        perror("Failed to allocate cmd->head (input.c) ->");
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
                j++;
                continue;
            }

            // Else break (end of head)
            break;
        }

        // If number of loops exceeds allocated size
        if (i >= target_size - 1)
        {
            // Safely reallocates new size by doubling space for new chars
            char * tmp_target = realloc(cmd->head, sizeof(char) * (target_size *= 2));

            if (tmp_target == NULL)
            {
                perror("Failed to re-allocate cmd->head (input.c) ->");
                free(cmd->head);
                return false;
            }

            // Assigns allocated space address to main variable
            cmd->head = tmp_target;
        }

        cmd->head[i++] = c;
        letterFound = true; // Assigns true for letter is found, proof after endline checks
        j++; // Increments for next character
    }

    // Assign last reserved space for null terminal
    cmd->head[i] = '\0';

    // Assign j as head size with additional pre-increment as j starts from 0
    cmd->target_size = ++j;

    return true;
}

// Function: getCommandBody
bool getCommandBody(Shell *shell, Command *cmd)
{
    int curr_c = cmd->target_size;
    char tmp_c = shell->commands[curr_c];

    // Checks for no body
    if (tmp_c == '\n' || tmp_c == '\0' || !tmp_c)
        return true;

    int argsSize = 1;
    cmd->args = malloc(sizeof(char *) * argsSize);

    // Assigns number of loops
    int i = 0;

    // Starts loop for arg list
    while (true)
    {
        // Updates current char for i > 0 for current arg
        tmp_c = shell->commands[curr_c];

        if (tmp_c == ' ')
        {
            // Skips for next argument
            curr_c++;
            continue;
        }

        // If end of command, break (no args left)
        if (tmp_c == '\n' || tmp_c == '\0' || !tmp_c)
            break;

        if (i == argsSize)
        {
            // Safely resizes allocated arg by +1 (Add new arg to the array)
            char ** tmp_args = realloc(cmd->args, (++argsSize) * sizeof(char *));

            if (tmp_args == NULL)
            {
                perror("Failed to re-allocate cmd->args (input.c) ->");

                // Cleans

                return false;
            }

            cmd->args = tmp_args;
        }

        int tmp_size = 32 * sizeof(char);
        char *tmp = malloc(tmp_size);

        if (tmp == NULL)
        {
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

                if (tmp_tmp == NULL)
                {
                    perror("Failed to re-allocate tmp (input.c) ->");

                    // Clean

                    return false;
                }

                tmp = tmp_tmp;
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
    return true;
}

// Function: isShellCommand
bool isShellCommand(char *head)
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
        if (strcmp(shellCmdTargets[i], head) == 0)
            return true;
    }

    // Return false for no match on commands
    return false;
}