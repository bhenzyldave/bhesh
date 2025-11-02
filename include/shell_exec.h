#ifndef SHELL_EXEC_H
#define SHELL_EXEC_H

// C Libraries
#include <stdbool.h>

// Included Headers
#include "datastructs.h"

bool manageCommands(Command * cmds);
void exec_external_commands(Command * cmd, bool * errno);
bool exec_internal_commands(Command * cmd);

/**
 * @brief Determines the type of a command (internal or external).
 * 
 * This function checks if the given command is a shell built-in command or an 
 * external command.
 * 
 * @param head Pointer to the string representing the main command.
 * @return bool Returns true if the command is a shell built-in command, 
 *         or false if it is an external command.
 */
bool get_exec_type(char *head);

#endif