#ifndef PROG_H
#define PROG_H

#include "prog.h" // Include if you need the SortParams definition for consistency

typedef struct {
    double *firstHalf;
    double *secondHalf;
    int firstSize;
    int secondSize;
    double firstAvg;
    double secondAvg;
    double *mergedArray; // Assuming the merged array will be stored here
    double overallAvg; // To store the computed overall average
} MergeParams;

void *mergeThread_avg(void *params);

typedef struct {
    double *subArray;
    int size;
    double average;
} SortParams;

void *sortThread_avg(void *params);

#endif