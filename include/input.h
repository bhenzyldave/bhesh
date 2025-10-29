#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include "datastructs.h"

bool fetchInput(char ** commands, size_t * cmd_size);
Command * getCommands(Shell * shell);
void handleCommands(Command cmd);
bool isSystem(char * target);
bool getTarget(Shell * shell, Command * cmd);
bool getArgs(Shell * shell, Command * cmd);

#endif