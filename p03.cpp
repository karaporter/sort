#include <chrono>
#include <string>
#include <fstream>
#include "p03.h"
#include "sorts.h"

using std::string;
using std::endl;
using std::ofstream;

int* ascendingArray(int lo, int n) {
    int start = lo;
    int stop = lo + n - 1;
    int* arr;
    arr = new int[n];
    arr[0] = lo;
    for (int i = 1; i <= n; i++) {
        arr[i] = start + 1;
        start += 1;
    }
return arr;
}

int* randomArray(int lo, int hi, int n) {
    int* randArr;
    randArr = new int[n];
    Random myRandomGenerator(lo, hi);
    for (int i = 0; i <= n; i++) {
        randArr[i] = myRandomGenerator.nextInt();
    }
return randArr;    
}

int* copyArray(int* array, int n) {
    int* copyArr;
    copyArr = new int[n];
    for (int i = 0; i <= n; i++) {
        copyArr[i] = array[i];
    }
return copyArr;    
}

Timing bubbleSort(int* array, int n) {
    Timing t;
    int temp;
    auto start = std::chrono::high_resolution_clock::now();
    for (int pass = 0; pass < n; pass++) {
        for (int j = 0; j < n - pass - 1; j++) {
            t.comparisons += 1;
            if (array[j + 1] < array[j]) {
                temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
                t.assignments += 3;
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> fp_ms = end - start;
    t.milliseconds = fp_ms.count();
    return t;
}

void generateLineChart(string filename, int sizes[],
                    double millis[][5], int numSizes) {
    ofstream outfile;
    outfile.open(filename);
outfile << "<!DOCTYPE html>\n";
outfile << "<html>\n";
outfile << "  <head>\n";
outfile << "    <script src=\"https://cdn.plot.ly/plotly-latest.min.js\"></script>\n";
outfile << "  </head>\n";
outfile << "  <body>\n";
outfile << "    <div id=\"plotcanvas\"></div>\n";
outfile << "    <script>\n";
outfile << "      var trace1 = {\n";
outfile << "        x: [";
        for (int i = 0; i < numSizes; i++) {
            outfile << sizes[i];
            outfile << ',';
        }
outfile << "],\n";
outfile << "        y: [";
        for (int i = 0; i < numSizes; i++) {
            outfile << millis[i][0];
            outfile << ',';
        }
outfile << "],\n";
outfile << "        mode: 'lines+markers',\n";
outfile << "        name: 'bubble'\n";
outfile << "      };\n";
outfile << "      var trace2 = {\n";
outfile << "        x: [";
        for (int i = 0; i < numSizes; i++) {
            outfile << sizes[i];
            outfile << ',';
        }
outfile << "],\n";
outfile << "        y: [";
        for (int i = 0; i < numSizes; i++) {
            outfile << millis[i][1];
            outfile << ',';
        }
outfile << "],\n";
outfile << "        mode: 'lines+markers',\n";
outfile << "        name: 'select'\n";
outfile << "      };\n";
outfile << "      var trace3 = {\n";
outfile << "        x: [";
        for (int i = 0; i < numSizes; i++) {
            outfile << sizes[i];
            outfile << ',';
        }
outfile << "],\n";
outfile << "        y: [";
        for (int i = 0; i < numSizes; i++) {
            outfile << millis[i][2];
            outfile << ',';
        }
outfile << "],\n";
outfile << "        mode: 'lines+markers',\n";
outfile << "        name: 'insert'\n";
outfile << "        x: [";
        for (int i = 0; i < numSizes; i++) {
            outfile << sizes[i];
            outfile << ',';
        }
outfile << "],\n";
outfile << "        y: [";
        for (int i = 0; i < numSizes; i++) {
            outfile << millis[i][3];
            outfile << ',';
        }
outfile << "],\n";
outfile << "        mode: 'lines+markers',\n";
outfile << "        name: 'merge'\n";
outfile << "      };\n";
outfile << "      var trace5 = {\n";
outfile << "        x: [";
        for (int i = 0; i < numSizes; i++) {
            outfile << sizes[i];
            outfile << ',';
        }
outfile << "],\n";
outfile << "        y: [";
        for (int i = 0; i < numSizes; i++) {
            outfile << millis[i][4];
            outfile << ',';
        }
outfile << "],\n";
outfile << "        mode: 'lines+markers',\n";
outfile << "        name: 'quick'\n";
outfile << "      };\n";
outfile << "      var data = [trace1,trace2,trace3,trace4,trace5,];\n";
outfile << "      var layout = {\n";
outfile << "        title: 'Sort Comparison',\n";
outfile << "        xaxis: { title: 'Data Size' },\n";
outfile << "        yaxis: { title: 'Time (ms)' }\n";
outfile << "      };\n";
outfile << "      Plotly.newPlot('plotcanvas', data, layout);\n";
outfile << "    </script>\n";
outfile << "  </body>\n";
outfile << "</html>\n";
}
