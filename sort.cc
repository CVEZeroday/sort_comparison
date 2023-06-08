// sort.h

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned long long swapCount;

void swap(int* a, int* b);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void insertionSort(int arr[], int low, int high);
void heapSort(int arr[], int size);
void heapify(int arr[], int size, int root);
int choosePivot(int arr[], int low, int high);
void introSortUtil(int arr[], int low, int high, int depthLimit);
void introSort(int arr[], int size);

long long get_nanoseconds();
long long GetTimerCountInNS(void);
long long qs_measureTime(int* arr, int size);
long long is_measureTime(int* arr, int size);

void swap(int* a, int* b)
{
  swapCount++;
  int temp = *a;
  *a = *b;
  *b = temp;
}


void quickSort(int arr[], int left, int right)
{
  int i = left, j = right;
  int pivot = arr[left];

  while (i <= j)
  {
    while (arr[i] < pivot) i++;
    while (arr[j] > pivot) j--;

    if (i <= j)
    {
      swap(&arr[i], &arr[j]);

      i++;
      j--;
    }
  }

  if (left < j) quickSort(arr, left, j);
  if (i < right) quickSort(arr, i, right);
}

void insertionSort(int arr[], int low, int high) {
  for (int i = low + 1; i <= high; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= low && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void heapSort(int arr[], int size) {
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(arr, size, i);
  }

  for (int i = size - 1; i >= 0; i--) {
    swap(&arr[0], &arr[i]);
    heapify(arr, i, 0);
  }
}

void heapify(int arr[], int size, int root) {
  int largest = root;
  int left = 2 * root + 1;
  int right = 2 * root + 2;

  if (left < size && arr[left] > arr[largest]) {
    largest = left;
  }

  if (right < size && arr[right] > arr[largest]) {
    largest = right;
  }

  if (largest != root) {
    swap(&arr[root], &arr[largest]);
    heapify(arr, size, largest);
  }
}

int choosePivot(int arr[], int low, int high) {
  int mid = low + (high - low) / 2;
  if (arr[low] > arr[mid])
    swap(&arr[low], &arr[mid]);
  if (arr[low] > arr[high])
    swap(&arr[low], &arr[high]);
  if (arr[mid] > arr[high])
    swap(&arr[mid], &arr[high]);

  swap(&arr[mid], &arr[high]);
  return arr[high];
}

void introSortUtil(int arr[], int low, int high, int depthLimit) {
  if (high - low > 16) {
    if (depthLimit == 0) {
      heapSort(arr + low, high - low + 1);
      return;
    }

    int pivot = choosePivot(arr, low, high);

    int i = low, j = high;

    while (i <= j)
    {
      while (arr[i] < pivot) i++;
      while (arr[j] > pivot) j--;

      if (i <= j)
      {
        swap(&arr[i], &arr[j]);

        i++;
        j--;
      }
    }
    introSortUtil(arr, low, j, depthLimit - 1);
    introSortUtil(arr, i, high, depthLimit - 1);
  } else {
    insertionSort(arr, low, high);
  }
}

void introSort(int arr[], int size) {
  int depthLimit = 2 * log(size);

  introSortUtil(arr, 0, size - 1, depthLimit);
}

// sort.cc

#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

//#define ARRAYLENGTH 100000

int len;
int* qs_sortedArray = 0;
int* is_sortedArray = 0;

int main() {
  long long len;
  int n;
  string file_name, _file_name;

  cout << "enter the length of data: ";
  cin >> len;

  cout << "enter the name of the data file: ";
  cin >> file_name;

  cout << "enter the count of test: ";
  cin >> n;

  milliseconds isMillSum(0);
  microseconds isMicSum(0);
  nanoseconds isNanoSum(0);
  unsigned long long isSwapCountSum = 0;
  
  milliseconds qsMillSum(0);
  microseconds qsMicSum(0);
  nanoseconds qsNanoSum(0);
  unsigned long long qsSwapCountSum = 0;

  for (int i = 0; i < n; i++)
  {
    _file_name = file_name + to_string(i) + ".txt";
    FILE *fp;
    fp = fopen(_file_name.c_str(), "r");
    if(fp == NULL)
    {
      cout << "file doesn't exist: " << file_name << "\n";
      return -1;
    }

    qs_sortedArray = (int*)malloc(len*4);

    for (long long i = 0; i < len; i++) {
      fscanf(fp, "%d", &qs_sortedArray[i]);
    }

    fclose(fp);

    printf("first: %d, last: %d\n\n", *qs_sortedArray, *(qs_sortedArray+len-1));
    is_sortedArray = (int*)malloc(len*4);
    memcpy(is_sortedArray, qs_sortedArray, len*4);

    cout << "\n======================================\n";
    cout << "# " << i;
    cout << "\n======================================\n";

    system_clock::time_point isStart = system_clock::now();
    swapCount = 0;
    introSort(is_sortedArray, len);
    system_clock::time_point isEnd = system_clock::now();

    milliseconds isMill = duration_cast<milliseconds>(isEnd - isStart);
    microseconds isMic = duration_cast<microseconds>(isEnd - isStart);
    nanoseconds isNano = isEnd - isStart;
  
    isMillSum += isMill;
    isMicSum += isMic;
    isNanoSum += isNano;
    isSwapCountSum += swapCount;

    cout << "IntroSort Result: smallest number is " << *is_sortedArray << ", biggest number is " << *(is_sortedArray + len - 1) << "\n";
    cout << "- IntroSort Elapsed time: " << isMill.count() << " ms\n";
    cout << "- IntroSort Elapsed time: " << isMic.count() << " microseconds\n";
    cout << "- IntroSort Elapsed time: " << isNano.count() << " nanoseconds\n";
    cout << "- IntroSort Swap Count: " << swapCount << "\n";

    cout << "\n======================================\n";

    system_clock::time_point qsStart = system_clock::now();
    swapCount = 0;
    quickSort(qs_sortedArray, 0, len-1);
    system_clock::time_point qsEnd = system_clock::now();

    milliseconds qsMill = duration_cast<milliseconds>(qsEnd - qsStart);
    microseconds qsMic = duration_cast<microseconds>(qsEnd - qsStart);
    nanoseconds qsNano = isEnd - isStart;

    qsMillSum += qsMill;
    qsMicSum += qsMic;
    qsNanoSum += qsNano;
    qsSwapCountSum += swapCount;

    cout << "QuickSort Result: smallest number is " << *qs_sortedArray << ", biggest number is " << *(qs_sortedArray + len - 1) << "\n";
    cout << "- QuickSort Elapsed time: " << qsMill.count() << " ms\n";
    cout << "- QuickSort Elapsed time: " << qsMic.count() << " microseconds\n";
    cout << "- QuickSort Elapsed time: " << qsNano.count() << " nanoseconds\n";
    cout << "- QuickSort Swap Count: " << swapCount << "\n";

    cout << "\n======================================\n";
    cout << "\n======================================\n";

    free(qs_sortedArray);
    free(is_sortedArray);
  }
    cout << "\n======================================\n";
    cout << "# average";
    cout << "\n======================================\n";

    cout << "- IntroSort Elapsed time: " << isMillSum.count() / n << " ms\n";
    cout << "- IntroSort Elapsed time: " << isMicSum.count() / n << " microseconds\n";
    cout << "- IntroSort Elapsed time: " << isNanoSum.count() / n << " nanoseconds\n";
    cout << "- IntroSort Swap Count: " << isSwapCountSum / n << "\n";

    cout << "\n======================================\n";

    cout << "- QuickSort Elapsed time: " << qsMillSum.count() / n << " ms\n";
    cout << "- QuickSort Elapsed time: " << qsMicSum.count() / n << " microseconds\n";
    cout << "- QuickSort Elapsed time: " << qsNanoSum.count() / n << " nanoseconds\n";
    cout << "- QuickSort Swap Count: " << qsSwapCountSum / n << "\n";

    cout << "\n======================================\n";
  return 0;
}
