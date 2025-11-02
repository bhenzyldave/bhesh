#ifndef SHELL_EXEC_H
#define SHELL_EXEC_H

// C Libraries
#include <stdbool.h>

// Included Headers
#include "datastructs.h"

bool manageCommands(Command * cmds, char * homedir);
bool exec_internal_commands(Command * cmd, bool * err_status, char * homedir);
void exec_external_commands(Command * cmd, bool * err_status);

#endif