#ifndef QUICKSORT_H
#define QUICKSORT_H
#include "vectordinamico.h"

unsigned long choose_pivot(unsigned long i, unsigned long j);
void quicksort(vectorD *vector, unsigned long beg, unsigned long end);

#endif /*QUICKSORT.H*/