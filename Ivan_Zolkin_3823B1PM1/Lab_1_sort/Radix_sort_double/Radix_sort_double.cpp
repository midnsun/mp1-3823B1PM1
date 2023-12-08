//Radix sort for DOUBLE
//coder: IVAN ZOLKIN
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
//#include "intrin.h"
//#pragma intrinsic(__rdtsc)

//qsort compare functions start
//int cmp(const void* a, const void* b)
//{
//    const double* ad, * bd;
//
//    ad = (const double*)a;
//    bd = (const double*)b;
//
//    if (*ad < *bd)
//    {
//        return -1;
//    }
//    else if (*ad > *bd)
//    {
//        return 1;
//    }
//    else
//    {
//        return 0;
//    }
//}
//qsort compare functions end

void swap(int* ptr1, int* ptr2) //swap variables
{
    int temp;
    temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void foffset(unsigned char* mas, int size, int offset, int count[257]) {
    int i = 0;
    int tmp;
    for (i = 0; i < 257; count[i++] = 0) {};
    for (i = 0; i < size; i++) {
        count[  //сounts byte values
            mas[offset + i * sizeof(double)]    //i-byte every digit
        ]++;
    }
    tmp = count[0]; //bytes == 0
    count[0] = 0;
    for (i = 0; i < 256; i++) {
        swap(&tmp, &count[i + 1]);
        count[i+1] += count[i];
    }
}

void radix_sort(double* mas, int size) {
    //start variables
    int i = 0, j = 0;
    unsigned int negativeDigits = 0;
    int count[257];
    double* tempp;
    double* mas2 = (double*)malloc(size * sizeof(double));
    unsigned char* pm = (unsigned char*)mas;    //Representation of a number in bytes
    //end variables
    
    for (; i < sizeof(double); i++) { //run for bytes (double -- 8byte (now))
        foffset(pm, size, i, count);
        for (j = 0; j < size; j++) {
            mas2[
                count[
                    pm[j * sizeof(double) + i]
                ]++
            ] = mas[j];
        }
        //start swap arrays
        tempp = mas;
        mas = mas2;
        mas2 = tempp;
        //end swap arrays
        pm = (unsigned char*)mas; //Representation of a number in bytes
    }
    //start counting negative elements
    for (i = size-1; i > -1; i--) {
        if (mas[i] >= 0) {
            break;
        }
        negativeDigits++;
    }
    //end counting negative elements
    //start pushing elements in mas2
    for (i = 0; i < negativeDigits; i++) {
        mas2[i] = mas[size - i - 1];
    }
    for (i = negativeDigits; i < size; i++) {
        mas2[i] = mas[i - negativeDigits];
    }
    //end pushing elements in mas2
    //start copy mas2 to mas
    for (i = 0; i < size; i++) {
        mas[i] = mas2[i];
    }
    //end copy mas2 to mas
    free(mas2);
}

int main() {
    int n, i = 0;
    //unsigned __int64 a, b; //tick test
    scanf("%d", &n);
    double* mas = (double*)malloc(n * sizeof(double));
    //double* mas_TRUE = (double*)malloc(n * sizeof(double));   //for correct test
    
    //random start
    /*for (; i < n; i++) {
        mas[i] = double(rand()) / RAND_MAX * 2000.0 - 1000.0;
        mas_TRUE[i] = mas[i];
    }*/
    //random end
    
    
    for (; i < n; i++) {
        scanf("%lf", &mas[i]);
    }    
    
    
    //tick test start   !UNCOMMENT inlude and pragma
    //a = __rdtsc();
    radix_sort(mas, n);
    //b = __rdtsc();
    //printf_s("%I64d ticks\n", b - a);
    //tick test end
    
    //correct test start  !UNCOMMENT cmp() function!
    /*qsort(mas_TRUE, n, sizeof(double), cmp);
    for (i = 0; i < n; i++) {
        if (!(mas[i] * mas[i] - mas_TRUE[i] * mas_TRUE[i] > -1e-6 && mas[i] * mas[i] - mas_TRUE[i] * mas_TRUE[i] < 1e-6)) {
            printf("ERROR! %lf %lf", mas[i], mas_TRUE[i]);
            return 1;
        }
    }
    printf("OK!");*/
    //correct test finish
    
    for (i = 0; i < n; i++) {
        printf("%lf ", mas[i]);
    }
    

    free(mas);

    return 0;
}
