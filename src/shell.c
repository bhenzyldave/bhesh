#include "bhesh.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

int main()
{
    Shell shell;
    int r1 = Shell_init(&shell);
    if (r1) return 1;
    
    Shell_loop(&shell);
    Shell_cleanup(&shell);
    return 0;
}