#define _CRT_SECURE_NO_WARNINGS
#include "SortLab.h"
#include <time.h>
#include <unistd.h>

int main(int args, const char* argv[]) {
    unsigned int seed = 5;
    size_t i;
    size_t size = 1000;
    size_t maxsize = 10000;
    size_t seqsize = 1000000;
    struct timespec start, stop;
    uint64_t time;
    FILE* fptr = NULL;
    TYPE* mas;
    uint64_t* seq = (uint64_t*)malloc(seqsize * sizeof(uint64_t));
    mas = (TYPE*)malloc(maxsize * sizeof(TYPE));
    fptr = fopen("times.txt", "w");

    if (fptr != NULL) {
        for (i = size; i < maxsize; i++) {
            fillm(mas, i, seed, -1.0, 1.0);
            fprintf(fptr, "%d", i);

            shake(mas, i);
            clock_gettime(CLOCK_REALTIME, &start);
            insertion(mas, i);
            clock_gettime(CLOCK_REALTIME, &stop);
            time = (stop.tv_nsec - start.tv_nsec) + (stop.tv_sec - start.tv_sec) * 1000000000;
            fprintf(fptr, " %d", time);

            shake(mas, i);
            seqPow2(seq, &seqsize, i);
            clock_gettime(CLOCK_REALTIME, &start);
            _shellsort(mas, i, seq, seqsize);
            clock_gettime(CLOCK_REALTIME, &stop);
            time = (stop.tv_nsec - start.tv_nsec) + (stop.tv_sec - start.tv_sec) * 1000000000;
            fprintf(fptr, " %d", time);

            shake(mas, i);
            clock_gettime(CLOCK_REALTIME, &start);
            _mergesort(mas, i);
            clock_gettime(CLOCK_REALTIME, &stop);
            time = (stop.tv_nsec - start.tv_nsec) + (stop.tv_sec - start.tv_sec) * 1000000000;
            fprintf(fptr, " %d", time);
            
            shake(mas, i);
            clock_gettime(CLOCK_REALTIME, &start);
            radix_sort_LSD(mas, i);
            clock_gettime(CLOCK_REALTIME, &stop);
            time = (stop.tv_nsec - start.tv_nsec) + (stop.tv_sec - start.tv_sec) * 1000000000;
            fprintf(fptr, " %d\n", time);

            printf("size: %d - writed\n", i);
        }
        fclose(fptr);
    }
    else {
        printf("File error\n");
    }

    
    free(seq);
    free(mas);
    return 0;
}
