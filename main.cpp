#include <iostream>
#include <iomanip>
#include <sstream>
#include "sorts.h"
#include "p03.h"

using std::cout;
using std::endl;
using std::setfill;
using std::setw;
using std::setprecision;
using std::stringstream;

enum ArrayType { SORTED, NEARLY_SORTED, RANDOM };


string generateTimingTable(Timing bubble,
                           Timing selection,
                           Timing insertion,
                           Timing merge,
                           Timing quick) {
    Timing t[] = {bubble, selection, insertion, merge, quick};
    string names[] = {"Bubble  ", "Select  ", "Insert  ",
                      "Merge   ", "Quick   "};

    stringstream s;
    s << "          Compares       Assigns         Millis" << endl;
    s << "        ------------   ------------   ------------" << endl;

    for (int i = 0; i < 5; i++) {
        s << names[i];
        s << setfill(' ') << setw(12) << t[i].comparisons;
        s << "   ";
        s << setfill(' ') << setw(12) << t[i].assignments;
        s << "   ";
        s << setfill(' ') << setw(12);
        s << setprecision(10) << t[i].milliseconds << endl;
    }

    return s.str();
}


void shuffle(int* array, int n, float percent) {
    int times = static_cast<int>(n * percent / 2.0);
    for (int i = 0; i < times; i++) {
        int a = rand() % n;
        int b = rand() % n;
        int temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }
}


void verifySortsActuallySort(int size) {
    const int NUM_SORTS = 5;
    const int N = size;
    const int LO = 0;
    const int HI = 999999;
    string sortNames[] = {"bubble", "selection", "insertion", "merge", "quick"};

    int* array = randomArray(LO, HI, N);
    for (int sort = 0; sort < NUM_SORTS; sort++) {
        int* copy = copyArray(array, N);
        if (sort == 0) {
            bubbleSort(copy, N);
        } else if (sort == 1) {
            selectionSort(copy, N);
        } else if (sort == 2) {
            insertionSort(copy, N);
        } else if (sort == 3) {
            mergeSort(copy, N);
        } else {
            quickSort(copy, N);
        }
        if (isSorted(copy, N)) {
            cout << sortNames[sort] << " sort works correctly." << endl;
        } else {
            cout << sortNames[sort] << " FAILS to sort." << endl;
        }
        delete [] copy;
    }
    delete [] array;
}


void fixedSizeTiming(int size, ArrayType arrayType=RANDOM) {
    const int NUM_SORTS = 5;
    const int TIMES = 10;
    const int N = size;
    const int LO = 0;
    const int HI = 999999;

    Timing timing[NUM_SORTS];

    for (int t = 0; t < TIMES; t++) {
        int* array;
        if (arrayType == SORTED) {
            array = ascendingArray(LO, N);
        } else if (arrayType == NEARLY_SORTED) {
            array = ascendingArray(LO, N);
            shuffle(array, N, 0.01);
        } else {
            array = randomArray(LO, HI, N);
        }
        for (int sort = 0; sort < NUM_SORTS; sort++) {
            int* copy = copyArray(array, N);
            Timing temp;
            if (sort == 0) {
                temp = bubbleSort(copy, N);
            } else if (sort == 1) {
                temp = selectionSort(copy, N);
            } else if (sort == 2) {
                temp = insertionSort(copy, N);
            } else if (sort == 3) {
                temp = mergeSort(copy, N);
            } else {
                temp = quickSort(copy, N);
            }
            timing[sort].comparisons += temp.comparisons;
            timing[sort].assignments += temp.assignments;
            timing[sort].milliseconds += temp.milliseconds;
            delete [] copy;
        }
        delete [] array;
    }

    for (int sort = 0; sort < NUM_SORTS; sort++) {
        timing[sort].comparisons /= TIMES;
        timing[sort].assignments /= TIMES;
        timing[sort].milliseconds /= TIMES;
    }

    cout << "Average performance over " << TIMES << " trials" << endl;
    if (arrayType == SORTED) {
        cout << "For a pre-sorted array of size " << N << endl;
    } else if (arrayType == NEARLY_SORTED) {
        cout << "For a nearly sorted array of size " << N << endl;
    } else {
        cout << "For a random array of size " << N << endl;
    }

    string output = generateTimingTable(timing[0], timing[1], timing[2],
                                        timing[3], timing[4]);
    cout << output << endl;
}


void increasingSizeTiming() {
    const int LO = 0;
    const int HI = 999999;
    const int NUM_SIZES = 10;
    const int NUM_SORTS = 5;
    int sizes[NUM_SIZES];
    double millis[NUM_SIZES][NUM_SORTS];
    int size = 64;
    for (int i = 0; i < NUM_SIZES; i++) {
        sizes[i] = size;
        size *= 2;
    }
    for (int i = 0; i < NUM_SIZES; i++) {
        int* array = randomArray(LO, HI, sizes[i]);
        for (int sort = 0; sort < NUM_SORTS; sort++) {
            int* copy = copyArray(array, sizes[i]);
            Timing t;
            if (sort == 0) {
                t = bubbleSort(copy, sizes[i]);
            } else if (sort == 1) {
                t = selectionSort(copy, sizes[i]);
            } else if (sort == 2) {
                t = insertionSort(copy, sizes[i]);
            } else if (sort == 3) {
                t = mergeSort(copy, sizes[i]);
            } else {
                t = quickSort(copy, sizes[i]);
            }
            delete [] copy;
            millis[i][sort] = t.milliseconds;
        }
        delete [] array;
    }

    generateLineChart("timings.html", sizes, millis, NUM_SIZES);
}

int main() {
    verifySortsActuallySort(1000);
    cout << endl;
    fixedSizeTiming(10000);
    cout << endl;
    fixedSizeTiming(10000, NEARLY_SORTED);
    cout << endl;
    fixedSizeTiming(10000, SORTED);

    increasingSizeTiming();
    cout << endl;
    cout << "A line chart comparison of the sorts is in timings.html." << endl;
    cout << "Open this file in your web browser to view it." << endl;

    return 0;
}
