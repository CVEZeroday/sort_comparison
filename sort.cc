// sort.cc

#include <chrono>
#include <iostream>

#include "sort.h"

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

    is_sortedArray = (int*)malloc(len*4);
    memcpy(is_sortedArray, qs_sortedArray, len*4);

    cout << "======================================\n";
    cout << "# " << i;
    printf("first: %d, last: %d\n", *qs_sortedArray, *(qs_sortedArray+len-1));
    cout << "======================================\n";

    system_clock::time_point qsStart = system_clock::now();
    swapCount = 0;
    quickSort(qs_sortedArray, 0, len-1);
    system_clock::time_point qsEnd = system_clock::now();

    milliseconds qsMill = duration_cast<milliseconds>(qsEnd - qsStart);
    microseconds qsMic = duration_cast<microseconds>(qsEnd - qsStart);
    nanoseconds qsNano = qsEnd - qsStart;

    qsMillSum += qsMill;
    qsMicSum += qsMic;
    qsNanoSum += qsNano;
    qsSwapCountSum += swapCount;

    cout << "QuickSort Result: smallest number is " << *qs_sortedArray << ", biggest number is " << *(qs_sortedArray + len - 1) << "\n";
    cout << "- QuickSort Elapsed time: " << qsMill.count() << " ms\n";
    cout << "- QuickSort Elapsed time: " << qsMic.count() << " microseconds\n";
    cout << "- QuickSort Elapsed time: " << qsNano.count() << " nanoseconds\n";
    cout << "- QuickSort Swap Count: " << swapCount << "\n";

    cout << "======================================\n";

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

    cout << "======================================\n";
    cout << "======================================\n";

    free(qs_sortedArray);
    free(is_sortedArray);
  }
    cout << "======================================\n";
    cout << "# average\n";
    cout << "======================================\n";

    cout << "- QuickSort Elapsed time: " << qsMillSum.count() / n << " ms\n";
    cout << "- QuickSort Elapsed time: " << qsMicSum.count() / n << " microseconds\n";
    cout << "- QuickSort Elapsed time: " << qsNanoSum.count() / n << " nanoseconds\n";
    cout << "- QuickSort Swap Count: " << qsSwapCountSum / n << "\n";
    cout << "======================================\n";

    cout << "- IntroSort Elapsed time: " << isMillSum.count() / n << " ms\n";
    cout << "- IntroSort Elapsed time: " << isMicSum.count() / n << " microseconds\n";
    cout << "- IntroSort Elapsed time: " << isNanoSum.count() / n << " nanoseconds\n";
    cout << "- IntroSort Swap Count: " << isSwapCountSum / n << "\n";
    cout << "======================================\n";

  return 0;
}
