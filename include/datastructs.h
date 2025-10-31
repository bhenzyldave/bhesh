#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
/*
    Defines a struct named Command 
    with the following data:

        - target -> This data represents the pointer
        of the memory allocated string of the target
        main command. Such as for instance:

            ~ >command arg1 arg2

            target = command which represents the main call.
            Where: target is a string

        - target_size -> Due to logical reasons,
        this variable acts as a pointer to the previous
        last char or the length of target (strlen(target))
        to be used on excluding the main command as argument.

        - args -> This represents as an array of strings where
        all arguments are stored. This points out to the memory
        allocated data. (More explanation on input.c -> getCommandBody())

        - args_size -> This represents as the size of the arguments
        stored. Such as the number of arguments.
*/
typedef struct
{
    char * target;
    int target_size;

    char ** args;
    int args_size;
} Command;

/*
    Defines a struct named Shell
    with the following data:

        - home_dir -> This holds the value of the current
        directory of the shell.

        - commands -> This points to the array of chars of
        the overall command input given by the shell user.

        -> prompt -> This represents the Prompt struct.
        (More information about it above)
*/
typedef struct
{
    char *home_dir;
    char *commands;
} Shell;

#endif