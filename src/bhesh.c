#include <stdlib.h>
#include <stdio.h>

#include "bhesh.h"
#include "prompt.h"

int Shell_init(Shell *self)
{
    self->commands = malloc(INITIAL_MAX_COMMANDS * sizeof(char));
    self->prompt = displayPrompt(" >", self);
}

int Shell_loop(Shell * self)
{
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