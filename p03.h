#ifndef __P03_H__
#define __P03_H__

#include <string>
#include "sorts.h"

using std::string;


int* ascendingArray(int lo, int n);
int* randomArray(int lo, int hi, int n);
int* copyArray(int* array, int n);
Timing bubbleSort(int* array, int n);
void generateLineChart(string filename, int sizes[], double millis[][5],
                       int numSizes);


#endif
