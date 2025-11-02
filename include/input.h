#ifndef INPUT_H
#define INPUT_H

// Includes C Library and Header
#include <stdbool.h>
#include "datastructs.h"

/**
 * @brief Fetches the shell user input.
 * 
 * This function reads the user's input from the shell and stores it in the 
 * provided `commands` buffer. The size of the buffer is updated in `cmd_size`.
 * 
 * @param commands Double pointer to the buffer where the input will be stored.
 * @param cmd_size Pointer to the size of the buffer.
 * @return bool Returns true on success, or false on failure.
 */
bool fetchInput(char **commands, size_t *cmd_size);

/**
 * @brief Parses the shell user input into a Command structure.
 * 
 * This function processes the user's input stored in the Shell structure 
 * and extracts the main command (head) and its arguments (body).
 * 
 * @param shell Pointer to the Shell structure containing the user's input.
 * @param cmds Pointer to the Command structure where the head will be stored.
 * @return bool Returns true on success, or false on failure.
 */
bool getCommands(Shell *shell, Command * cmds);

/**
 * @brief Extracts the main command (head) from the user's input.
 * 
 * This function retrieves the main command (head) from the user's input 
 * stored in the Shell structure and stores it in the Command structure.
 * 
 * @param shell Pointer to the Shell structure containing the user's input.
 * @param cmd Pointer to the Command structure where the head will be stored.
 * @return bool Returns true on success, or false on failure.
 */
bool getCommandHead(Shell *shell, Command *cmd);

/**
 * @brief Extracts the arguments (body) from the user's input.
 * 
 * This function retrieves the arguments (body) from the user's input stored 
 * in the Shell structure and stores them in the Command structure.
 * 
 * @param shell Pointer to the Shell structure containing the user's input.
 * @param cmd Pointer to the Command structure where the arguments will be stored.
 * @return bool Returns true on success, or false on failure.
 */
bool getCommandBody(Shell *shell, Command *cmd);

#endif