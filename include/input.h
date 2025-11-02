#ifndef INPUT_H
#define INPUT_H

// Includes C Library and Header
#include <stdbool.h>
#include "datastructs.h"

/*
    Declares function: fetchInput with double pointer
    char commands and a pointer size_t cmdsize as
    arguments.

    Usage: To fetch the shell user input. (More information
    about it on input.c -> fetchInput())
*/
bool fetchInput(char ** commands, size_t * cmd_size);

/*
    Declares function: getCOmmands with struct Shell
    as main argument from datastructs.h -> Shell.

    Usage: To get the commands from the shell user input
    such as: head as main command and args as the arguments
    of the commands (More information about it on input.c -> getCommands())
*/
Command * getCommands(Shell * shell);

/*
    Declares function: handleCommands with struct Command 
    as the main argument from datastructs.h -> Command.

    Usage: -
*/
void handleCommands(Command cmd);

/*
    Declares function: isShellCommand with a pointer of 
    head as main argument.

    Usage: Returns a value true if the main command
    is a shell built-in command, else false. This
    function is used to differentiate built-in shell
    commands and external commands.
*/
bool isShellCommand(char * head);

/*
    Declares function: getCommandHead with struct Shell
    and struct Command as aguments.

    Usage: To get the main command (head).
    (More information about it on input.c -> getCommandHead())
*/
bool getCommandHead(Shell * shell, Command * cmd);

/*
    Declares function: getCommandBody with struct Shell
    and struct Command as arguments.

    Usage: To get the arguments of the shell user
    input command (args). (More information about it
    on input.c -> getCommandBody())
*/
bool getCommandBody(Shell * shell, Command * cmd);

#endif