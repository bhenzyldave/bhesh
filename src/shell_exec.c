// C Libraries
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

// Included Headers
#include "shell_exec.h"
#include "input.h"

// Function: manageCommands
bool manageCommands(Command *cmds)
{
    // HANDLE PIPES LATER

    // Checks if the command is external
    if (get_exec_type(cmds->head))
    {
        return exec_internal_commands(cmds);
    }

    // Run internal commands
    bool errno = true;
    exec_external_commands(cmds, &errno);
    return errno;
}

// Function: exec_external_commands
void exec_external_commands(Command *cmd, bool * errno)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed: (shell_exec.h) ->");
        *errno = false;
    }

    if (pid == 0)
    {
        // Size of the command (+2 for head and NULL)
        int size = cmd->body_size + 2;
        char **args = malloc(size * sizeof(char *));
        int n = 1;

        // Attach head at the beginning
        args[0] = malloc((strlen(cmd->head) * sizeof(char)) + 1);
        strcpy(args[0], cmd->head);

        // Attach command arguments
        while (true)
        {
            // Checks if command body is already attached
            if ((n - 1) == cmd->body_size)
                break;

            args[n] = malloc((strlen(cmd->body[n - 1]) * sizeof(char)) + 1);
            strcpy(args[n], cmd->body[n - 1]);
            n++;
        }

        // Attaches NULL at the end
        args[n] = NULL;

        // Execute the external command and check for errors
        if (execvp(args[0], args) == -1)
        {
            fprintf(stderr, "'%s |-> No such command exists! :(\n", args[0]);
            *errno = false;

            for (int r = 0; args[r] != NULL; r++)
                free(args[r]);

            free(args);

            exit(1);
        }

    }
    else
        wait(NULL);
}

// Function: exec_internal_commands
bool exec_internal_commands(Command *cmd)
{
    // Checks if shell user is trying to exit
    if ((strcmp(cmd->head, "exit") == 0) && (cmd->body_size == 0))
        return false;

    return true;
}

// Function: get_exec_type
bool get_exec_type(char *head)
{
    // Maintainer Note: Add more commands later

    // Initializes built-in shell commands
    char *shellCmdTargets[] = {"cd", "pwd", "export", "exit"};

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