//
// Created by Sergey Fedorov on 08/02/2020.
//

#include <stdlib.h>

int print_ints(const int ints[], int length){
    for (int i = 0; i < length; ++i) {
        printf("%i ", ints[i]);
    }
    printf("\n");
}

int int_comparator (const void *a, const void *b) {
    return ( *(int*)a - *(int*)b );
}

void qsort_ints(int *values, int length) {
    qsort(values, length, sizeof(int), int_comparator);
}