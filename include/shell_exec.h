#ifndef SHELL_EXEC_H
#define SHELL_EXEC_H

// C Libraries
#include <stdbool.h>

// Included Headers
#include "datastructs.h"

bool manageCommands(Command * cmds, Shell * shell);
bool exec_internal_commands(Command * cmd, bool * err_status, Shell * shell, bool * isExternal);
void exec_external_commands(Command * cmd, bool * err_status);
CMD_Node * createExecList(Command * cmds, Shell * shell);

#endif
