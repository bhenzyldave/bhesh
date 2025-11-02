#ifndef BHESH_H
#define BHESH_H

// Includes "datastructs.h" from bhesh/include
#include "datastructs.h"

/**
 * @brief Initializes the Shell data structure.
 * 
 * @param self Pointer to the Shell structure (defined in datastructs.h).
 * @return int Returns 0 on success, or 1 on failure.
 */
int Shell_init(Shell *self);

/**
 * @brief Cleans up memory allocated for the Shell structure.
 * 
 * @param self Pointer to the Shell structure (defined in datastructs.h).
 */
void Shell_cleanup(Shell *self);

/**
 * @brief Starts the main shell loop, keeping the program running.
 * 
 * @param self Pointer to the Shell structure (defined in datastructs.h).
 * @return int Returns 0 on success, or 1 on failure.
 */
int Shell_run(Shell *self);

#endif