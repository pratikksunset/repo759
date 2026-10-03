#include "scan.h"
#include <random>
#include <chrono>
#include <ratio>
#include <iostream>
#include <cmath>
#include <cstdio>

using std::cout;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int argc, char* argv[]) {

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_sec;

    int n = std::atoi(argv[1]);
    
    float* array = new float[n];
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

    for (int i = 0; i < n; i++) {
        array[i] = dis(gen);
    }

    float* output = new float[n]();

    start = high_resolution_clock::now();
    scan(array, output, n);
    end = high_resolution_clock::now();


    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    cout << duration_sec.count() <<"\n";
    cout << output[0] << "\n";
    cout << output[n-1] << "\n";

    delete[] array;
    delete[] output;

    return 0;
}