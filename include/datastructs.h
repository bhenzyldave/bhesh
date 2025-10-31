#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

typedef struct
{
    char *memPrompt;
    int length;
} Prompt;

typedef struct
{
    char * target;
    int target_size;

    char ** args;
    int args_size;
} Command;

typedef struct
{
    int os_type;
    char *home_dir;
    char *commands;
    Prompt *prompt;
} Shell;

#endif