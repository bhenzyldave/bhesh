#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "input.h"

bool fetchInput(char **commands, size_t *cmd_size)
{
    int c = 0;
    int i = 0;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (i >= (*cmd_size) - 1)
        {
            *commands = realloc(*commands, ((*cmd_size) *= 2));

            if (*commands == NULL)
            {
                perror("Failed to allocate commands (input.c) ->");
                return true;
            }
        }

        (*commands)[i++] = (char)c;
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
    printf("%d\n", cmds->target_size);

    bool gA = getArgs(shell, cmds);
    printf("%d\n", cmds->args_size);

    return cmds;

    if (gT || gA )
    {
        perror("Failed to getTarget or getArgs (input.c) ->");
        return NULL;
    }

    return cmds;
}

bool getTarget(Shell *shell, Command *cmd)
{
    int target_size = 64; // 2 as 1 for first char of shell->commands and '\0'
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