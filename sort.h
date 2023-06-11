// sort.h
#ifndef _SORT_H_
#define _SORT_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned long long swapCount;

void swap(int* a, int* b);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void insertionSort(int arr[], int low, int high);
void heapSort(int arr[], int size);
void heapify(int arr[], int size, int root);
int choosePivot(int arr[], int low, int high);
void introSortUtil(int arr[], int low, int high, int depthLimit);
void introSort(int arr[], int size);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _SORT_H_
