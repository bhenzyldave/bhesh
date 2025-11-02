// C Libraries
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Included Headers
#include "utilities.h"

// Function: get_curr_dir
char *get_curr_dir()
{
    size_t size = 128 * sizeof(char);
    char *cwd; // Declares cwd string

    // Starts loop
    while (true)
    {
        // Allocates cwd with size data
        cwd = malloc(size);

        if (cwd == NULL)
        {
            perror("\nFailed to allocate cwd! (prompt.c) : get_curr_dir()) -> ");
            return NULL;
        }

        // Get cwd and if successful, break
        if (getcwd(cwd, size) != NULL) 
            break;

        free(cwd);
        size *= 2;
    }

    // If successful, return cwd
    return cwd;
}