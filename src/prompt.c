// Includes C Libraries
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

// Includes Headers
#include "prompt.h"
#include "bhesh.h"

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
            perror("Failed to allocate cwd! (prompt.c: get_curr_dir()) -> ");
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

// Function: printInterface
// (More information about shell_indicator, c1, and c2 on prompt.h)
void printInterface(char *shell_indicator, Shell *shell, char c1, char c2)
{
    // Get the current directory
    char *cwd = get_curr_dir();

    if (cwd == NULL)
    {
        perror("Failed to fetch current directory (prompt.c: get_curr_dir()) ->");
        
        // Clean and exit
    }

    // If cwd is equal to HOME path
    if (strcmp(cwd, shell->home_dir) == 0)
    {
        // Safely resizes cwd by 2 chars
        char * tmp_cwd = realloc(cwd, 2 * sizeof(char));

        if (tmp_cwd == NULL)
        {
            perror("Failed to re-allocate cwd (prompt.c) ->");

            // Clean and exit
        }

        // Changes main variable with new memory address
        cwd = tmp_cwd;

        // Assigns ~ as for home directory
        cwd[0] = '~';
        cwd[1] = '\0';
    }

    // Prints shell interface as default: " ~ >"
    printf("%c%s%c%s", c1, cwd, c2, shell_indicator);
    free(cwd); // Frees cwd (clean up)
}