#include "stdio.h"
#include <algorithm>
#include <cmath>
#include <time.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

#define uchar unsigned char 

void bubbleSort(float* a, int n)
{
	int i, j, flag;
	for (i = 0; i < n - 1; i++)
	{
		flag = 1;
		for (j = n - 1; j > i; j--)
		{
			if (a[j] < a[j - 1])
			{
				std::swap(a[j], a[j - 1]);
				flag = 0;
			}
		}
		if (flag) break;
	}
	return;
}

void shellSort(float* a, int n)
{
	int step, i, j;

	for (step = 1; step < (n - 1) / 9; step = 3 * step + 1); //1 4 13 40 121 364 1093
	for (; step > 0; step /= 3)
	{
		for (i = step; i < n; i++)
		{
			for (j = i; j >= step && a[j] < a[j - step]; j -= step)
				std::swap(a[j], a[j - step]);
		}
	}
	return;
}

uchar getByte(float* item, int numberByte)
{
	return ((uchar*)item)[numberByte];
}

void radixSort(float* a, int n)
{
	float* b;
	int* count, d, i, j, mid;
	
	b = (float*)malloc(n * sizeof(float));
	count = (int*)malloc(257 * sizeof(int));

	for (d = 0; d < sizeof(float); d++)
	{
		for (j = 0; j < 257; j++) count[j] = 0;
		for (i = 0; i < n; i++) count[getByte(&a[i], d) + 1]++;
		for (j = 1; j < 257; j++) count[j] += count[j - 1];
		for (i = 0; i < n; i++) b[count[getByte(&a[i], d)]++] = a[i];
		for (i = 0; i < n; i++) a[i] = b[i];
	}

	for (i = 0; i < n; i++)
	{
		if (a[i] < 0)
		{
			mid = i;
			break;
		}
	}

	j = 0;
	for (i = n - 1; i >= mid; i--) a[j++] = b[i];
	for (i = 0; i < mid; i++) a[j++] = b[i];

	free(count);
	free(b);
	return;
}

void merege(float* a, float* b, float* res, int an, int bn)
{
	int ia = 0, ib = 0, ir;
	for (ir = 0; ir < an + bn; ir++)
	{
		if (ia == an) { res[ir] = b[ib++]; continue; }
		if (ib == bn) { res[ir] = a[ia++]; continue; }
		res[ir] = (b[ib] > a[ia]) ? a[ia++] : b[ib++];
	}
	return;
}

void meregeSort(float* a, int n)
{
	float* b;
	int step, i, k;
	b = (float*)malloc(n * sizeof(float));
	step = 1;
	k = 0;
	for (i = 0; i < n; i++) b[i] = a[i];
	for (; step < n; step *= 2)
	{
		for (i = 0; i < n; i += 2 * step)
		{
			merege(a + i, a + i + step, b + i, std::max(0, std::min(step, n - i)), std::max(0, std::min(step, n - step - i)));
		}
		std::swap(a, b);
		k++;
	}
	
	if (k % 2)
	{
		std::swap(a, b);
		for (i = 0; i < n; i++) a[i] = b[i];
	}
	free(b);
	return;
}

void printArray(float* a, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%f ", a[i]);
	}
	printf("\n");
	return;
}

void randomFilling(float* mas, int n, int a, int b)
{
	int i;
	for (i = 0; i < n; i++)
	{
		mas[i] = (a + ((float)rand() / RAND_MAX) * abs(b - a));
	}
	
	return;
}

int compareFloat(const void* a, const void* b)
{
	float arg1, arg2;
	arg1 = *(const float*)a;
	arg2 = *(const float*)b;

	if (arg1 < arg2) return -1;
	if (arg1 > arg2) return 1;
	return 0;
}

int main()
{
	int n, i, numberSort, checkCorrect;
	float* a;
	float* b;
	clock_t st, en;
	double seconds;

	scanf("%i%i", &numberSort, &checkCorrect);
	if (numberSort < 0 || numberSort > 3)
	{
		printf("number sort incorrect");
		return 0;
	}
	if (checkCorrect != 0 && checkCorrect != 1)
	{
		printf("incorrect value");
		return 0;
	}
	if (numberSort == 0) printf("bubbleSort\n");
	if (numberSort == 1) printf("shellSort\n");
	if (numberSort == 2) printf("meregeSort\n");
	if (numberSort == 3) printf("radixSort\n");

	srand(time(NULL));
	for (n = 10; n < 1e9; n *= 100)
	{
		a = (float*)malloc(n * sizeof(float));
		b = (float*)malloc(n * sizeof(float));
		if (a == NULL || b == NULL)
		{
			printf("not memory");
			return -1;
		}
		printf("%i\n", n);

		randomFilling(a, n, -1000, 1000);
		for (i = 0; i < n; i++) b[i] = a[i];

		//printArray(a, n);
		st = clock();
		if (numberSort == 0) bubbleSort(a, n);
		if (numberSort == 1) shellSort(a, n);
		if (numberSort == 2) meregeSort(a, n);
		if (numberSort == 3) radixSort(a, n);
		en = clock();

		seconds = (double)(en - st) / CLOCKS_PER_SEC;
		//printArray(a, n);
		qsort(b, n, sizeof(float), compareFloat);
		if (checkCorrect) for (i = 0; i < n; i++)
		{
			if (b[i] != a[i])
			{
				printf("sort incorrect");
				return 0;
			}
		}

		printf("%f\n", seconds);

		free(a);
		free(b);
	}
	if (checkCorrect) printf("sort correct");
    return 0;
}