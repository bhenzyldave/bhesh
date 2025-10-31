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
                return false;
            }
        }

        (*commands)[i++] = (char)c;
    }

    if (c != 0)
        (*commands)[i] = '\0';

    return true;
}

void handleCommands(Command cmd)
{
}

Command *getCommands(Shell *shell)
{
    Command *cmds = malloc(sizeof(Command));

    cmds->args = NULL;
    cmds->args_size = 0;
    cmds->target = NULL;
    cmds->target_size = 0;

    if (cmds == NULL)
    {
        perror("Failed to getCommandHead or getCommandBody (input.c) ->");
        return NULL;
    }

    bool gT = getCommandHead(shell, cmds);

    if (!gT)
    {
        perror("Failed to getCommandHead or getCommandBody (input.c) ->");
        free(cmds);
        return NULL;
    }

    printf("%s\n", (char *)cmds->target);
    printf("%d\n", cmds->target_size);

    return cmds;

    bool gA = getCommandBody(shell, cmds);

    if (!gA)
    {
        perror("Failed to getCommandHead or getCommandBody (input.c) ->");
        free(cmds);
        return NULL;
    }


    printf("%s\n", cmds->args[0]);
    printf("%d\n", cmds->args_size);

    return cmds;
}

bool getCommandHead(Shell *shell, Command *cmd)
{
    int target_size = 64; // 2 as 1 for first char of shell->commands and '\0'
    cmd->target = malloc(target_size * sizeof(char));

    if (cmd->target == NULL)
    {
        perror("Failed to allocate cmd->target (input.c) ->");
        return false;
    }

    bool letterFound = false;

    int i = 0;
    int j = 0;

    while (true)
    {
        char c = shell->commands[j]; // Current char

        if (c == '\0' || c == '\n' || c == ' ' || !c)
        {
            if (c == ' ' && !letterFound)
            {
                j++;
                continue;
            }

            break;
        }

        if (i >= target_size - 1)
        {
            target_size *= 2;
            cmd->target = realloc(cmd->target, sizeof(char) * target_size);

            if (cmd->target == NULL)
            {
                perror("Failed to re-allocate cmd->target (input.c) ->");
                free(cmd->target);
                return false;
            }
        }

        j++;
        cmd->target[i++] = c;
        letterFound = true;
    }

    cmd->target[i] = '\0';
    cmd->target_size = j;

    return true;
}

bool getCommandBody(Shell *shell, Command *cmd)
{
    int curr_c = cmd->target_size;
    char tmp_c = shell->commands[curr_c];

    if (tmp_c == '\n' || tmp_c == '\0' || !tmp_c) return false;

    int argsSize = 1;
    cmd->args = malloc(sizeof(char *) * argsSize);


    int i = 0;

    while (true)
    {
        if (i == argsSize)
        {
            cmd->args = realloc(cmd->args, (++argsSize) * sizeof(char *));

            if (cmd->args == NULL)
            {
                perror("Failed to re-allocate cmd->args (input.c) ->");
            }
        }

        tmp_c = shell->commands[curr_c];

        if (tmp_c == ' ')
        {
            curr_c++;
            continue;
        }

        if (tmp_c == '\n' || tmp_c == '\0' || !tmp_c)
            break;

        int tmp_size = 32;
        char *tmp = malloc(sizeof(char) * tmp_size);
        int j = 0;

        while (true)
        {
            if (j >= tmp_size - 1)
            {
                tmp = realloc(tmp, sizeof(char) * tmp_size);

                if (tmp == NULL)
                {
                    perror("Failed to re-allocate tmp (input.c) ->");
                }
            }

            tmp_c = shell->commands[curr_c++];

            if (tmp_c == '\n' || tmp_c == ' ' 
                || tmp_c == '\0' || !tmp_c)
                break;

            tmp[j++] = tmp_c;
        }

        strcpy(cmd->args[i++], tmp);
        free(tmp);
    }

    cmd->args_size = argsSize;
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