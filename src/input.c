#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "input.h"

bool getCommands(char **commands, size_t cmd_size)
{
    int i = 0;
    int c = 0;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (i < cmd_size - 1)
        {
            (*commands)[i++] = (char)c;
        }
        else
        {
            *commands = realloc(*commands, cmd_size * 2);

            if (*commands == NULL)
            {
                perror("Failed to re-allocate self->commands (bhesh.c) ->");
                return 1;
            }
        }
    }

    if (c != 0)
        (*commands)[i] = '\0';

    return 0;
}

void handleCommands(char **commands)
{
    
}