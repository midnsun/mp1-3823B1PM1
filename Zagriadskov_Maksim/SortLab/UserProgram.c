#define _CRT_SECURE_NO_WARNINGS
#include "SortLab.h"
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
void sleep(uint64_t time) { Sleep(time*1000); }
#else
#include <unistd.h>
#endif

const size_t seq_marc_size = 9;
uint64_t seq_marc[9] = { 1750,701,301,132,57,23,10,4,1 };

int main(int args, const char* argv[]) {
    size_t i;
    TYPE temp = 0.0f;
    char sorttype = 0;
    size_t size = 1000;
    size_t seqsize = 1000000;
    unsigned int seed = 0;
    TYPE left = 0.0;
    TYPE right = 0.0;
    clock_t time;
    TYPE* mas;
    uint64_t* seq = (uint64_t*)malloc(seqsize * sizeof(uint64_t));
    mas = (TYPE*)malloc(1 * sizeof(TYPE));
    
    printf("Welcome to SortLab program!\n");
    sleep(2);
    while (sorttype != 'q') {
        printf("Choose sort to work with: \n");
        printf("q for qiut program, i for insertion sort, s for shell sort, m for merge sort, r for radix sort: \n");
        scanf(" %c", &sorttype);
        printf("Enter the size of the array: \n");
        scanf(" %d", &size);
        free(mas);
        mas = (TYPE*)malloc(size * sizeof(TYPE));
        printf("0 to fill the array randomly, 1 to fill the array manually: \n");
        scanf(" %d", &seed);
        if (seed == 1) {
            for (i = 0; i < size; i++) {
                scanf( "%f", &temp);
                mas[i] = temp;
            }
        }
        else if (seed == 0) {
            printf("Enter the seed to generate data: \n");
            scanf(" %d", &seed);
            printf("Enter the left border: \n");
            scanf(" %f", &left);
            printf("Enter the right border: \n");
            scanf(" %f", &right);

            fillm(mas, size, seed, left, right);
        }
        else {
            printf("Wrong input\n");
            return 0;
        }

        switch (sorttype)
        {
        case 'q':
            printf("Thank you for using this program!\n");
            return 0;
        case 'i':
            printf("The array is sorting... \n");
            time = clock();
            insertion(mas, size);
            time = clock() - time;
            break;
        case 's':
            printf("What seqence do you want to use? 0 for size/2 seq, 1 for 2^i seq, 2 for 2^i*3^i seq, 3 for emperic seq (size up to 4000 only)\n");
            scanf(" %c", &sorttype);
            if (sorttype == '0') {
                seqHalfSize(seq, &seqsize, size);
                printf("The array is sorting... \n");
                time = clock();
                _shellsort(mas, size, seq, seqsize);
                time = clock() - time;
            }
            else if (sorttype == '1') {
                seqPow2(seq, &seqsize, size);
                printf("The array is sorting... \n");
                time = clock();
                _shellsort(mas, size, seq, seqsize);
                time = clock() - time;
            }
            else if (sorttype == '2') {
                seqPow2Pow3(seq, &seqsize, size);
                printf("The array is sorting... \n");
                time = clock();
                _shellsort(mas, size, seq, seqsize);
                time = clock() - time;
            }
            else if (sorttype == '3') {
                printf("The array is sorting... \n");
                time = clock();
                _shellsort(mas, size, seq_marc, seq_marc_size);
                time = clock() - time;
            }
            else {
                printf("Wrong input\n");
                return 0;
            }
            break;
        case 'm':
            printf("The array is sorting... \n");
            time = clock();
            _mergesort(mas, size);
            time = clock() - time;
            break;
        case 'r':
            printf("The array is sorting... \n");
            time = clock();
            radix_sort_LSD(mas, size);
            time = clock() - time;
            break;
        default:
            printf("Wrong input\n");
            return 0;
        }

        printf("The array was successfully sorted!\n ");
        printf("Approximate time was: %d ms\n", time);
        printf("Print it? y/n\n");
        scanf(" %c", &sorttype);
        if (sorttype == 'y') mprint(mas, size);
        else if (sorttype == 'n') continue;
        else {
            printf("Wrong input\n");
            return 0;
        }
    }
    
    free(seq);
    free(mas);
    printf("Thank you for using this program!\n");
    scanf(" %c", &sorttype);
    return 0;
}
