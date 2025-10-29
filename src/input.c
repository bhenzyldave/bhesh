#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "input.h"

bool fetchInput(char **commands, size_t *cmd_size)
{
    int i = 0;
    int c = 0;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (i < *cmd_size - 1)
        {
            (*commands)[i++] = (char)c;
        }
        else
        {
            *commands = realloc(*commands, *cmd_size * 2);
            *cmd_size *= 2;

            if (*commands == NULL)
            {
                perror("Failed to re-allocate self->commands (bhesh.c) ->");
                return true;
            }
        }
    }

    if (c != 0)
        (*commands)[i] = '\0';

    return false;
}

void handleCommands(Command cmd)
{
}

Command *getCommands(Shell *shell)
{
    Command *cmds = malloc(sizeof(Command));

    if (cmds == NULL)
    {
        perror("Failed to getTarget or getArgs (input.c) ->");
        return NULL;
    }

    bool gT = getTarget(shell, cmds);
    bool gA = getArgs(shell, cmds);

    if (!gT || !gA)
    {
        perror("Failed to getTarget or getArgs (input.c) ->");
        return NULL;
    }

    return cmds;
}

// FIX THIS PLS
bool getTarget(Shell *shell, Command *cmd)
{
    cmd->target = malloc(sizeof(char) * 2);

    if (cmd->target == NULL)
    {
        perror("Failed to re-allocate cmd->args (input.c) ->");
        return false;
    }

    int i = 0;
    int j = 0;
    size_t target_size = 2;

    while (true)
    {
        char c = shell->commands[i];

        if (c == ' ' || c == '\0' || c == '\n' || !c)
        {
            if (c == ' ')
            {
                i++;
                j++;
                continue;
            }

            break;
        }

        i -= j;
        j = 0;

        if (i < target_size - 1)
        {
            cmd->target[i++] = c;
        }
        else
        {
            cmd->target = realloc(cmd->target, target_size * 2);
            target_size *= 2;

            if (cmd->target == NULL)
            {
                perror("Failed to re-allocate cmd->target (input.c) ->");
                return false;
            }
        }
    }

    cmd->target[i] = '\0';
}

// FIX THIS PLS
bool getArgs(Shell *shell, Command *cmd)
{
    cmd->args = malloc(sizeof(char *));

    if (cmd->args == NULL)
    {
        perror("Failed to re-allocate cmd->args (input.c) ->");
        return false;
    }

    int i = 0;
    int starting_point = 0; // Index
    size_t args_size = 1;

    while (true)
    {
        if (i >= args_size)
        {
            cmd->args = realloc(cmd->args, args_size * 2);
            args_size *= 2;

            if (cmd->args == NULL)
            {
                perror("Failed to re-allocate cmd->args (input.c) ->");
                return false;
            }
        }

        // String pointer array
        cmd->args[i] = malloc(sizeof(char) * 2);

        if (cmd->args[i] == NULL)
        {
            perror("Failed to re-allocate cmd->args (input.c) ->");
            if (i > 0)
            {
                for (int k = i; 0 < k; k--)
                    free(cmd->args[k]);
            }

            free(cmd->args);
            return false;
        }

        int k = 0; // J helper
        int j = starting_point;
        size_t args_c_size = 2;
        char c;

        while (true)
        {
            if (j >= args_c_size - 1)
            {
                cmd->args[i] = realloc(cmd->args[i], args_c_size * 2);
                args_c_size *= 2;

                if (cmd->args[i] == NULL)
                {
                    perror("Failed to re-allocate cmd->args (input.c) ->");
                    if (i > 0)
                    {
                        for (int k = i; 0 < k; k--)
                            free(cmd->args[i]);
                    }

                    free(cmd->args);
                    return false;
                }
            }

            c = shell->commands[j];

            if (c == '\n' || c == '\0' || c == ' ' || !c)
            {
                if (c == ' ')
                {
                    k++;
                    j++;
                    continue;
                }

                break;
            }

            j -= k;
            k = 0;

            cmd->args[i][j] = c;
            j++;
        }

        cmd->args[i][j] = '\0';

        starting_point = j;
        i++;
    }
}

bool isSystem(char *target)
{
    // Add more commands later
    char *shellCmdTargets[] = {
        "cd", "pwd", "export", "exit"};

    // Explicitly state the number of shell commands for performance reasons
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(shellCmdTargets[i], target) == 0)
            return true;
    }

    return false;
}