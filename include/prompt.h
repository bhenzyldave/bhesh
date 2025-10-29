#ifndef PROMPT_H
#define PROMPT_H

#include "datastructs.h"

Prompt * displayPrompt(char * promptInitial, Shell * shell);
char * get_curr_dir();

#endif