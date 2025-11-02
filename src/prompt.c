// Includes C Libraries
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <pwd.h>

// Includes Headers
#include "prompt.h"
#include "bhesh.h"
#include "utilities.h"

// Function: printInterface
// (More information about shell_indicator, c1, and c2 on prompt.h)
bool printInterface(char *shell_indicator, Shell *shell, char c1, char c2)
{
    // Get the current directory
    char *cwd = get_curr_dir();

    if (cwd == NULL)
    {
        perror("\nFailed to fetch current directory (prompt.c: get_curr_dir()) ->");
        free(cwd);
        return false;
    }

    // If cwd is equal to HOME path
    if (strcmp(cwd, shell->home_dir) == 0)
    {
        // Safely resizes cwd by 2 chars
        char * tmp_cwd = realloc(cwd, 2 * sizeof(char));

        if (tmp_cwd == NULL)
        {
            perror("\nFailed to re-allocate cwd (prompt.c) ->");
            free(cwd);
            return false;
        }

        // Changes main variable with new memory address
        cwd = tmp_cwd;

        // Assigns ~ as for home directory
        cwd[0] = '~';
        cwd[1] = '\0';
    }

    char * user = getenv("USER");
    struct passwd * pw = getpwuid(0);
    char * root_user;

    if (user == NULL)
        user = "null";

    if (pw == NULL)
    {
        root_user = "null";
    }

     root_user = pw->pw_name;

    // Prints shell interface as default: "(user) ~ >"
    printf("(%s@%s)%c%s%c%s", root_user, user, c1, cwd, c2, shell_indicator);
    free(cwd); // Frees cwd (clean up)
    return true;
}