#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

/**
 * @struct Command
 * @brief Represents a parsed shell command with its arguments.
 * 
 * This structure holds the main command (head) and its arguments.
 * 
 * Members:
 * - `head`: Pointer to the memory-allocated string representing the main command.
 *   Example: For the input `command arg1 arg2`, `head` would be "command".
 * - `head_length`: Represents the length of the `head` string (strlen(head)).
 *   Used to exclude the main command when processing arguments.
 * - `body`: Array of strings where all arguments are stored.
 *   Points to memory-allocated data.
 * - `body_size`: Number of arguments stored in `body`.
 */
typedef struct
{
    char *head;       /**< Pointer to the main command string. (Allocated) */
    int head_length;  /**< Length of the `head` string. */

    char **body;      /**< Array of strings representing arguments. (Allocated) */
    int body_size;    /**< Number of arguments in `body`. */
} Command;

/**
 * @struct Shell
 * @brief Represents the shell's state and data.
 * 
 * This structure holds information about the shell's current state,
 * including the home directory and the user's input commands.
 * 
 * Members:
 * - `home_dir`: Pointer to the string representing the current directory of the shell.
 * - `commands`: Pointer to the memory-allocated string of the user's input commands.
 */
typedef struct
{
    char *home_dir;   /**< Pointer to the current directory string. (Not allocated) */
    char *commands;   /**< Pointer to the user's input commands. (Allocated) */
} Shell;

#endif