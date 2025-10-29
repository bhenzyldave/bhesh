#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#define INITIAL_MAX_COMMANDS 256

typedef struct
{
    char *memPrompt;
    int length;
} Prompt;

typedef struct
{
    char * target;
    char ** args;
} Command;

typedef struct
{
    int os_type;
    char *home_dir;
    char *commands;
    Prompt *prompt;
} Shell;

#endif