#include <chrono>
#include "sorts.h"


Random::Random(int lo, int hi) {
    std::random_device rd;
    generator = new std::mt19937(rd());
    distribution = new std::uniform_int_distribution<>(lo, hi);
}

Random::~Random() {
    delete generator;
    delete distribution;
}

int Random::nextInt() {
    return (*distribution)(*generator);
}


bool isSorted(int* array, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}


Timing selectionSort(int* array, int n) {
    Timing t;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            t.comparisons += 1;
            if (array[j] < array[min]) {
                min = j;
            }
        }
        if (min != i) {
            int temp = array[min];
            array[min] = array[i];
            array[i] = temp;
            t.assignments += 3;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> fp_ms = end - start;
    t.milliseconds = fp_ms.count();
    return t;
}


Timing insertionSort(int* array, int n) {
    Timing t;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < n; i++) {
        int x = array[i];
        int j = i - 1;
        int s = 0;
        while (j >= 0 && array[j] > x) {
            t.comparisons += 1;
            s += 1;
            array[j + 1] = array[j];
            t.assignments += 1;
            j = j - 1;
        }
        array[j + 1] = x;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> fp_ms = end - start;
    t.milliseconds = fp_ms.count();
    return t;
}


Timing merge(int* array, int alo, int ahi, int blo, int bhi, int lo, int hi) {
    Timing t;
    int* c = new int[hi - lo + 1];
    int ai = alo, bi = blo, ci = 0;
    while (ai <= ahi && bi <= bhi) {
        if (array[ai] < array[bi]) {
            c[ci++] = array[ai++];
        } else {
            c[ci++] = array[bi++];
        }
        t.comparisons += 1;
        t.assignments += 1;
    }
    while (ai <= ahi) {
        c[ci++] = array[ai++];
        t.assignments += 1;
    }
    while (bi <= bhi) {
        c[ci++] = array[bi++];
        t.assignments += 1;
    }
    ci = 0;
    for (int i = lo; i <= hi; i++) {
        array[i] = c[ci++];
        t.assignments += 1;
    }
    delete [] c;
    return t;
}

Timing mergeSort(int* array, int lo, int hi) {
    Timing t;
    if (lo < hi) {
        int mid = (hi + lo) / 2;
        Timing t1 = mergeSort(array, lo, mid);
        Timing t2 = mergeSort(array, mid + 1, hi);
        Timing t3 = merge(array, lo, mid, mid + 1, hi, lo, hi);
        t.comparisons = t1.comparisons + t2.comparisons + t3.comparisons;
        t.assignments = t1.assignments + t2.assignments + t3.assignments;
    }
    return t;
}

Timing mergeSort(int* array, int n) {
    Timing t;
    auto start = std::chrono::high_resolution_clock::now();
    t = mergeSort(array, 0, n - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> fp_ms = end - start;
    t.milliseconds = fp_ms.count();
    return t;
}


int partition(int* array, int lo, int hi, Timing& timing) {
    int pivot = lo;
    int i = lo + 1;
    int j = hi;
    while (i <= j) {
        while (i <= j && array[i] <= array[pivot]) {
            timing.comparisons += 1;
            i++;
        }
        while (i <= j && array[j] > array[pivot]) {
            timing.comparisons += 1;
            j--;
        }
        if (i <= j) {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            timing.assignments += 3;
        }
    }
    int temp = array[pivot];
    array[pivot] = array[j];
    array[j] = temp;
    timing.assignments += 1;
    return j;
}

void choosePivot(int* array, int lo, int hi, Timing& timing) {
    int pivot = (rand() % (hi - lo + 1)) + lo;
    int temp = array[lo];
    array[lo] = array[pivot];
    array[pivot] = temp;
    timing.assignments += 3;
}

Timing quickSort(int* array, int lo, int hi) {
    Timing t;
    if (lo < hi) {
        choosePivot(array, lo, hi, t);
        int p = partition(array, lo, hi, t);
        Timing t1 = quickSort(array, lo, p - 1);
        Timing t2 = quickSort(array, p + 1, hi);
        t.comparisons += t1.comparisons + t2.comparisons;
        t.assignments += t1.assignments + t2.assignments;
    }
    return t;
}

Timing quickSort(int* array, int n) {
    Timing t;
    auto start = std::chrono::high_resolution_clock::now();
    t = quickSort(array, 0, n - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> fp_ms = end - start;
    t.milliseconds = fp_ms.count();
    return t;
}
