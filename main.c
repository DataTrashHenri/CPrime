#include <stdio.h>
#include <time.h>

#include "chunk.h"

int main(void) {
    clock_t start = clock();
    sieve(100038098944ULL,(20000000));
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time: %.2f seconds\n", time_spent);

    return 0;
}
