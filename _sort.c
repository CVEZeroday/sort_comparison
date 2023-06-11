// _sort.c
#include "sort.h"

unsigned long long swapCount;

void swap(int* a, int* b)
{
  swapCount++;
  int temp = *a;
  *a = *b;
  *b = temp;
}


void quickSort(int* arr, int left, int right)
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

void insertionSort(int arr[], int low, int high)
{
  for (int i = low + 1; i <= high; i++)
  {
    int key = arr[i];
    int j = i - 1;

    while (j >= low && arr[j] > key)
      {
        arr[j + 1] = arr[j];
        j--;
      }
    arr[j + 1] = key;
  }
}

void heapSort(int arr[], int size)
{
  for (int i = size / 2 - 1; i >= 0; i--)
  {
    heapify(arr, size, i);
  }

  for (int i = size - 1; i >= 0; i--)
  {
    swap(&arr[0], &arr[i]);
    heapify(arr, i, 0);
  }
}

void heapify(int arr[], int size, int root)
{
  int largest = root;
  int left = 2 * root + 1;
  int right = 2 * root + 2;

  if (left < size && arr[left] > arr[largest])
  {
    largest = left;
  }

  if (right < size && arr[right] > arr[largest])
  {
    largest = right;
  }

  if (largest != root)
  {
    swap(&arr[root], &arr[largest]);
    heapify(arr, size, largest);
  }
}

int choosePivot(int arr[], int low, int high)
{
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

void introSortUtil(int arr[], int low, int high, int depthLimit)
{
  if (high - low > 16)
  {
    if (depthLimit == 0)
    {
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

void introSort(int* arr, int size)
{
  int depthLimit = 2 * log(size);

  introSortUtil(arr, 0, size - 1, depthLimit);
}

