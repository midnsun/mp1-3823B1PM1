//Merge sort for DOUBLE
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

int max(int a, int b) { //return max value
    if (a > b) {
        return a;
    }
    return b;
}
int min(int a, int b) { //return min value
    if (a < b) {
        return a;
    }
    return b;
}
void merge(double* a, double* b, double* res, int an, int bn) //unite two arrays in one ordered array 'res'
{
    int ia = 0, ib = 0, ir = 0;
    while (an > ia && ib < bn) //two pointer on 'a' and 'b', if element from 'a' < el from 'b' --> res.append(a[ia]) and move pointer on next element else append(b[bi]), bi++
    {
        if (a[ia] < b[ib]) {
            res[ir++] = a[ia++];
        }
        else {
            res[ir++] = b[ib++];
        }
    }
    /*
    after 'while' one of the pointers on the edge and we put the remaining elements
    */
    for (; ia < an; ia++) {
        res[ir++] = a[ia];
    }
    for (; ib < bn; ib++) {
        res[ir++] = b[ib];
    }
}
void merge_s(double* mas, int n) {
    int step = 1, i;
    double* temp;
    double* tmpdata = (double*)malloc(n * sizeof(double));
    for (; step < n; step *= 2) {
        for (i = 0; i < n; i += 2 * step) {
            merge(&mas[i], &mas[i + step], &tmpdata[i], max(0, min(step, n - i)), max(0, min(step, n - step - i)));
            /* arguments merge(1,2,3,4,5):
                1 - pointer on the beginning of first subarray (double*)
                2 - pointer on the beginning of second subarray (double*)
                3 - res array (double*)
                4 - length of the first array (int)
                5 - length of the second array (int)
            */
        }
        temp = mas; //swap res array and original array for using true data
        mas = tmpdata;
        tmpdata = temp;
    }
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
    merge_s(mas, n);
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