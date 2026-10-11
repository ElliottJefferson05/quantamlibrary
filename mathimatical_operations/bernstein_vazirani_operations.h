#ifndef BERNSTEIN_VAZIRANI_OPERATIONS_H
#define BERNSTEIN_VAZIRANI_OPERATIONS_H

#include "../quantomlibrary.h"

/* Allocate length search qubits plus one ancilla and run the gate circuit.
 * The low length qubits contain secret; qubit length finishes in |1>.
 * Returns NULL for invalid inputs or allocation failure.
 * Free the returned register with quantom_free(). */
Quantom_register *Bernstein_Vazirani(int length, int secret);

void Bernstein_Vazirani_Oracle(Quantom_register *q, int secret, int length);

#endif
