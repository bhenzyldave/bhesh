#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

bool getCommands(char ** commands, size_t cmd_size);
void handleCommands(char ** commands);

#endif