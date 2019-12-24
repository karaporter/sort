#ifndef __P03_SORTS_H__
#define __P03_SORTS_H__

#include <random>
#include <cstdint>


class Random {
 public:
    Random(int lo, int hi);
    ~Random();
    int nextInt();

 private:
    std::mt19937* generator;
    std::uniform_int_distribution<>* distribution;
};

struct Timing {
    std::int64_t comparisons;
    std::int64_t assignments;
    double milliseconds;
    Timing() : comparisons(0), assignments(0), milliseconds(0) {}
};

bool isSorted(int* array, int n);
Timing insertionSort(int* array, int n);
Timing selectionSort(int* array, int n);
Timing mergeSort(int* array, int n);
Timing quickSort(int* array, int n);


#endif
