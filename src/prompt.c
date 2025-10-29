#include "prompt.h"
#include "bhesh.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

char * get_curr_dir()
{
    size_t size = 128;    
    char * cwd;

    while(true)
    {
        cwd = malloc(size);
        
        if (cwd == NULL)
        {
            perror("Failed to allocate cwd! (prompt.c: get_curr_dir()) -> ");
            return NULL;
        }

        if (getcwd(cwd, size) != NULL)
            break;

        free(cwd);
        if (errno != ERANGE)
        {
            perror("Unexpected Error (prompt.c: errno not ERANGE) ->");
            return NULL;
        }

        size *= 2;        
    }

    return cwd;
}

Prompt *displayPrompt(char * promptCursor, Shell * shell)
{
    char * cwd = get_curr_dir(); 
    
    if (cwd == NULL)
    {
        perror("Failed to fetch current directory (prompt.c: get_curr_dir()) ->");
        free(cwd);
        Shell_cleanup(shell);
        exit(EXIT_FAILURE);
    }

    // Note: +3 for [] and null terminator -> "\n"
    char * promptCurrent = malloc((strlen(cwd) + strlen(promptCursor) + 3));
    sprintf(promptCurrent, "[%s]%s", cwd, promptCursor);

    // Note: +1 for null terminator -> "\n" from sprintf()
    Prompt *prompt = malloc(sizeof(Prompt)); 
    prompt->memPrompt = malloc(strlen(promptCurrent) * sizeof(char) + 1);

    if (prompt->memPrompt == NULL)
    {
        perror("Failed to allocate memory! (prompt.c: char * prompt) ->");
        free(prompt);
        free(promptCurrent);
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