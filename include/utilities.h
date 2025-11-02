#ifndef UTILITIES_H
#define UTILITIES_H

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