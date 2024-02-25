#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "prog.h"

void *sortThread_avg(void *params);  // Sort a portion of the array
void *mergeThread_avg(void *params); // Merge two sorted portions

// Insertion sort implementation
void insertionSort(double *array, int size)
{
    int i, j;
    double key;
    for (i = 1; i < size; i++)
    {
        key = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

// Thread function for sorting and averaging
void *sortThread_avg(void *params)
{
    SortParams *sortParams = (SortParams *)params;
    insertionSort(sortParams->subArray, sortParams->size);
    int i;
    double sum = 0;
    for (i = 0; i < sortParams->size; i++)
    {
        sum += sortParams->subArray[i];
    }
    sortParams->average = sum / sortParams->size;

    pthread_exit(NULL);
}

// Merge two sorted sub-arrays
void mergeArrays(double *first, int firstLen, double *second, int secondLen, double *merged)
{
    int i = 0, j = 0, k = 0;
    while (i < firstLen && j < secondLen)
    {
        if (first[i] < second[j])
        {
            merged[k++] = first[i++];
        }
        else
        {
            merged[k++] = second[j++];
        }
    }

    // Copy the remaining elements of first[], if there are any
    while (i < firstLen)
    {
        merged[k++] = first[i++];
    }

    // Copy the remaining elements of second[], if there are any
    while (j < secondLen)
    {
        merged[k++] = second[j++];
    }
}

// Thread function for merging and computing overall average
void *mergeThread_avg(void *params)
{
    MergeParams *mergeParams = (MergeParams *)params;

    // Assuming mergedArray has been allocated enough space
    mergeArrays(mergeParams->firstHalf, mergeParams->firstSize, mergeParams->secondHalf, mergeParams->secondSize, mergeParams->mergedArray);

    // Compute the overall average
    mergeParams->overallAvg = (mergeParams->firstAvg * mergeParams->firstSize + mergeParams->secondAvg * mergeParams->secondSize) / (mergeParams->firstSize + mergeParams->secondSize);

    pthread_exit(NULL);
}

void generateRandomArray(double *array, int size)
{
    int i;
    srand(time(NULL));
    for (i = 0; i < size; i++)
    {
        array[i] = 1.0 + (rand() / (RAND_MAX / (1000.0 - 1.0)));
    }
}

void printArray(double *array, int size)
{
    int i;
    for (i = 0; i < size && i < 10; i++)
    { // Limited to the first 10 elements as to not clog up the console
        printf("%f ", array[i]);
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <array_size>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    double *A = malloc(N * sizeof(double));
    if (!A)
    {
        perror("Failed to allocate memory for array A");
        return -1;
    }

    struct timespec start, end;
    double elapsed_single, elapsed_double;

    generateRandomArray(A, N);
    // printArray(A, N);

    // Two-threaded sort
    clock_gettime(CLOCK_MONOTONIC, &start);
    insertionSort(A, N);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_double = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("Sorting is done in %.6fms when two threads are used\n", elapsed_double);

    generateRandomArray(A, N);
    // printArray(A, N);

    // Single-threaded sort
    clock_gettime(CLOCK_MONOTONIC, &start);
    insertionSort(A, N);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_single = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("Sorting is done in %.6fms when one thread is used\n", elapsed_single);

    free(A);
    return 0;
}
