#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "bhesh.h"
#include "prompt.h"
#include "input.h"

int Shell_init(Shell *self)
{
#if defined(_WIN32) || defined(_WIN64)
    self->home_dir = getenv("HOMEDRIVER")
#elif defined(__linux__)
    self->home_dir = getenv("HOME");
#elif defined(__APPLE__) && define(__MACH__)
    self->home_dir = getenv("HOME");
#else
    perror("Unknown operating system!\n");
    return 1;
#endif

        chdir(&*self->home_dir);

    self->commands = malloc(INITIAL_MAX_COMMANDS * sizeof(char));
    self->prompt = displayShell("-> ", self);

    return 0;
}

int Shell_loop(Shell *self)
{
    size_t curr_command_size = INITIAL_MAX_COMMANDS;
    while (true)
    {
        bool fetchResult = fetchInput(self->commands, &curr_command_size);

        if (fetchResult)
            return 1;

        Command *cmds = getCommands(self);

        if (cmds == NULL)
            return 1;

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