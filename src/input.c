#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "input.h"

bool fetchInput(char *commands, size_t *cmd_size)
{
    int i = 0;
    int c = 0;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (i < *cmd_size - 1)
        {
            (commands)[i++] = (char)c;
        }
        else
        {
            commands = realloc(commands, *cmd_size * 2);
            *cmd_size *= 2;

            if (commands == NULL)
            {
                perror("Failed to re-allocate self->commands (bhesh.c) ->");
                return true;
            }
        }
    }

    if (c != 0)
        (commands)[i] = '\0';

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

    if (gT || gA)
    {
        perror("Failed to getTarget or getArgs (input.c) ->");
        return NULL;
    }

    return cmds;
}

bool getTarget(Shell *shell, Command *cmd)
{
    int target_size = 2; // 2 as 1 for first char of shell->commands and '\0'
    cmd->target = malloc(sizeof(char) * target_size);

    if (cmd->target == NULL)
    {
        perror("Failed to allocate cmd->target (input.c) ->");
        return true;
    }

    int i = 0;
    int j = 0;

    while (true)
    {
        char c = shell->commands[j]; // Current char

        if (c == '\0' || c == '\n' || c == ' ' || !c)
        {
            if (c == ' ' && i == 0)
            {
                j++;
            }

            break;
        }

        if (i >= target_size - 1)
        {
            cmd->target = realloc(cmd->target, sizeof(char) * (target_size *= 2));

            if (cmd->target == NULL)
            {
                perror("Failed to re-allocate cmd->target (input.c) ->");
                return true;
            }
        }

        cmd->target[i++] = c;
    }

    cmd->target[i] = '\0';
    return false;
}

bool getArgs(Shell *shell, Command *cmd)
{
    cmd->args = malloc(sizeof(char *));

    if (cmd->args == NULL)
    {
        perror("Failed to allocate cmd->args (input.c) ->");
        return false;
    }

    int size_p1 = 1;

    int i = strlen(cmd->target_size);
    int j = 0;

    while (true)
    {
        cmd->args[j] = malloc(sizeof(char) * 2); // 2 for 1 char space and '\0'

        if (cmd->args == NULL)
        {
            perror("Failed to allocate cmd->args (input.c) ->");
            return false;
        }

        int k = 0;
        int h = 0;
        int size_p2 = 2;

        while (true)
        {
            char c = shell->commands[i++]; // Increment after assignation

            if (c == '\0' || c == '\n' || !c || c == ' ')
            {
                if (c == ' ')
                {
                    i++;
                    continue;
                }

                break;
            }

            if (k >= size_p2 - 1)
            {
                cmd->args[j] = realloc(cmd->args[j], sizeof(char) * (size_p2 *= 2));

                if (cmd->args[j] == NULL)
                {
                    perror("Failed to re-allocate cmd->args (input.c) -> ");
                    free(cmd->args);
                    return false;
                }
            }

            cmd->args[j][k++] = c;
        }

        cmd->args[j][k] = '\0';
        cmd->args = realloc(cmd->args, (size_p1 *= 2) * sizeof(char *));

        if (cmd->args == NULL)
        {
            perror("Failed to re-allocate cmd->args (input.c) ->");
            return false;
        }
    }

    cmd->args_size = j;
    return true;
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