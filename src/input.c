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

    printf("%d\n", cmds->target_size);

    bool gA = getArgs(shell, cmds);

    printf("%d\n", cmds->args_size);

    return cmds;

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
    cmd->target = malloc(target_size);

    if (cmd->target == NULL)
    {
        perror("Failed to allocate cmd->target (input.c) ->");
        return true;
    }

    int i = 0;
    int j = 0;

    while (true)
    {
        char c = shell->commands[j++]; // Current char

        if (c == '\0' || c == '\n' || c == ' ' || !c)
        {
            if (c == ' ' && i == 0)
            {
                j++;
                continue;
            }

            break;
        }

        if (i >= target_size - 1)
        {
            cmd->target = realloc(cmd->target, target_size *= 2);

            if (cmd->target == NULL)
            {
                perror("Failed to re-allocate cmd->target (input.c) ->");
                return true;
            }
        }

        cmd->target[i++] = c;
    }

    cmd->target[i] = '\0';
    cmd->target_size = j;

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

    int args_size = 1;
    int i = 0;

    bool ongoing = true;
    while (ongoing)
    {
        // WHILE #1
        if (i >= args_size)
        {
            cmd->args = realloc(cmd->args, sizeof(char *) * (++args_size));

            if (cmd->args == NULL)
            {
                perror("Failed to allocate cmd->args (input.c) ->");
                return false;
            }

            continue;
        }
        // WHILE #1

        // WHILE #2
        int arg_nsize = 2; // 2 for 1 char space and '\0'
        char *tmp = malloc(arg_nsize);

        if (tmp == NULL)
        {
            perror("Failed to allocate cmd->args (input.c) ->");

            for (int n = 0; n < args_size; n++)
            {
                free(cmd->args[n]);
            }

            free(cmd->args);
            return false;
        }

        int k = cmd->target_size;
        int j = 0;

        while (true)
        {
            char c = shell->commands[k++]; // Current char

            printf("HERE -> %c", c);

            if (c == ' ')
                continue;

            if (c == '\0' || c == '\n' || !c)
            {
                ongoing = false;
                break;
            }

            if (j >= arg_nsize - 1)
            {
                tmp = realloc(tmp, arg_nsize *= 2);

                if (tmp == NULL)
                {
                    perror("Failed to re-allocate cmd->args (input.c) ->");

                    for (int n = 0; n < args_size; n++)
                    {
                        free(cmd->args[n]);
                    }

                    free(cmd->args);
                    return false;
                }
            }

            tmp[j] = c;
        }

        tmp[j] = '\0';
        cmd->args[i] = malloc(arg_nsize);
        strcpy(cmd->args[i], tmp);
        // WHILE #2

    }
    cmd->args_size = args_size;
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