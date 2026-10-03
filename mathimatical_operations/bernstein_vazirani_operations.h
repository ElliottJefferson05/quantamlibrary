#ifndef BERNSTEIN_VAZIRANI_OPERATIONS_H
#define BERNSTEIN_VAZIRANI_OPERATIONS_H

#include "../quantomlibrary.h"

void Bernstein_Vazirani(Quantom_register *q, int secret, int length);

void Bernstein_Vazirani_Oracle(Quantom_register *q, int secret, int length);

#endif
