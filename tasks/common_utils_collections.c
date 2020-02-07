//
// Created by Sergey Fedorov on 08/02/2020.
//

#include <stdlib.h>

int int_comparator (const void *a, const void *b) {
    return ( *(int*)a - *(int*)b );
}

void qsort_ints(int *values, int length) {
    qsort(values, length, sizeof(int), int_comparator);
}