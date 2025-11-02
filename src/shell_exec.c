// C Libraries
#include <string.h>
#include <stdio.h>

// Included Headers
#include "shell_exec.h"
#include "input.h"

// Function: manageCommands
bool manageCommands(Command * cmds)
{
    // HANDLE PIPES LATER

    // Sepates the command type
    if (get_exec_type(cmds->head))
    {
        return exec_internal_commands(cmds);
    }

    return exec_external_commands(cmds);
}


bool exec_external_commands(Command * cmd)
{
    return true;
}

bool exec_internal_commands(Command * cmd)
{
    if ((strcmp(cmd->head, "exit") == 0) && (cmd->body_size == 0))
        return false;

    

    return true;
}

// Function: get_exec_type
bool get_exec_type(char *head)
{
    // Maintainer Note: Add more commands later

    // Initializes built-in shell commands
    char *shellCmdTargets[] = { "cd", "pwd", "export", "exit" };

    // Explicitly state the number of shell commands for performance reasons
    // Where number of strings on shellCmdTargets - 1 is on i < n
    for (int i = 0; i < 4; i++)
    {
        // If it matches command, return true
        if (strcmp(shellCmdTargets[i], head) == 0)
            return true;
    }

    // Return false for no match on commands
    return false;
}