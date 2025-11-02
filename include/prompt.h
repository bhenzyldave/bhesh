#ifndef PROMPT_H
#define PROMPT_H

// Includes Header
#include "datastructs.h"

/**
 * @brief Updates and prints the shell interface.
 * 
 * This function updates the shell interface based on the provided 
 * `shell_indicator`, `c1`, and `c2` values. The interface format is:
 * 
 * Format: c1 + ~ + c2 + shell_indicator
 * 
 * Default values:
 * - `c1 = ' '`
 * - `c2 = ' '`
 * - `shell_indicator = '>'`
 * 
 * Example: Default Shell Interface: " ~ >"
 * 
 * @param shell_indicator Pointer to the string representing the shell prompt.
 * @param shell Pointer to the Shell structure.
 * @param c1 Character representing the first part of the interface.
 * @param c2 Character representing the second part of the interface.
 * @return bool Returns true on success, or false on failure.
 */
bool printInterface(char *shell_indicator, Shell *shell, char c1, char c2);

/**
 * @brief Retrieves the current working directory.
 * 
 * This function returns the current working directory as a dynamically 
 * allocated string. The caller is responsible for freeing the memory.
 * 
 * @return char* Pointer to the string representing the current directory.
 *         Returns NULL on failure.
 */
char *get_curr_dir();

#endif