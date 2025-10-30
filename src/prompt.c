#include "prompt.h"
#include "bhesh.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

char *get_curr_dir()
{
    // Initial size
    size_t size = 128;
    char *cwd;

    while (true)
    {
        cwd = malloc(size);

        if (cwd == NULL)
        {
            perror("Failed to allocate cwd! (prompt.c: get_curr_dir()) -> ");
            return NULL;
        }

        // If successful, break
        if (getcwd(cwd, size) != NULL)
            break;

        free(cwd);
        size *= 2;
    }

    return cwd;
}

// c1 & c2 refers to the brackets
Prompt *displayShell(char *promptCursor, Shell *shell, char c1, char c2)
{
    char *cwd = get_curr_dir();

    if (cwd == NULL)
    {
        perror("Failed to fetch current directory (prompt.c: get_curr_dir()) ->");
        Shell_cleanup(shell);
        exit(EXIT_FAILURE);
    }

    if (strcmp(cwd, shell->home_dir) == 0)
    {
        cwd = realloc(cwd, 2);
        cwd[0] = '~';
        cwd[1] = '\0';
    }

    // Note: +3 for [] and null terminator -> "\n"
    char *promptCurrent = malloc((strlen(cwd) + strlen(promptCursor) + 3));
    sprintf(promptCurrent, "%c%s%c%s", c1, cwd, c2, promptCursor);

    // Note: +1 for null terminator -> "\n" from sprintf()
    Prompt *prompt = malloc(sizeof(Prompt));
    prompt->memPrompt = malloc(strlen(promptCurrent) + 1);

    if (prompt->memPrompt == NULL)
    {
        perror("Failed to allocate memory! (prompt.c: char * prompt) ->");
        free(prompt);
        free(promptCurrent);
        free(cwd);
        Shell_cleanup(shell);
        exit(EXIT_FAILURE);
    }

    strcpy(prompt->memPrompt, promptCurrent);

    // Note: +1 for null terminator -> "\n"
    prompt->length = strlen(promptCurrent) + 1;

    printf("%s", prompt->memPrompt);
    free(promptCurrent);
    free(cwd);
    return prompt;
}