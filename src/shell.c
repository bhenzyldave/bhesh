#include "bhesh.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

int main()
{
    Shell shell;
    Shell_init(&shell);
    Shell_loop(&shell);
    Shell_cleanup(&shell);
    return 0;
}