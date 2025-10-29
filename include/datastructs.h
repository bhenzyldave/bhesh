#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#define INITIAL_MAX_COMMANDS 256

typedef struct {
    char * memPrompt;
    int length;
} Prompt;

typedef struct {
   char * commands;
   Prompt * prompt;
} Shell;

#endif