#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "bhesh.h"
#include "prompt.h"
#include "input.h"

int Shell_init(Shell *self)
{
#if defined(_WIN32) || defined(_WIN64)
    self->os_type = 0;
#elif defined(__linux__)
    self->os_type = 1;
#elif defined(__APPLE__) && define(__MACH__)
    self->os_type = 2;
#else
    perror("Unknown operating system!\n");
    return 1;
#endif

    switch (self->os_type)
    {
    case 0:
        self->home_dir = getenv("HOMEDRIVER");
        break;
    case 1:
        break;
    case 2:
        break;
    }

    // self->home_directory;
    self->commands = malloc(INITIAL_MAX_COMMANDS * sizeof(char));
    self->prompt = displayShell(" >", self);
}

int Shell_loop(Shell *self)
{
    size_t curr_command_size = INITIAL_MAX_COMMANDS;
    while (true)
    {
        bool r = getCommands(&self->commands, curr_command_size);
        if (r)
            return 1;
        handleCommands(&self->commands);

        displayShell(" >", self);
    }
}

void Shell_cleanup(Shell *self)
{
    if (self->commands != NULL)
        free(self->commands);

    if (self->prompt != NULL)
    {
        if (self->prompt->memPrompt != NULL)
            free(self->prompt->memPrompt);

        free(self->prompt);
    }
}