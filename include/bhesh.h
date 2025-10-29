#ifndef BHESH_H
#define BHESH_H

#include "datastructs.h"

int Shell_init(Shell *self);
void Shell_cleanup(Shell *self);
int Shell_loop(Shell * self);

#endif