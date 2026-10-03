#include "convolution.h"
#include <random>
#include <chrono>
#include <ratio>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstddef>

using std::cout;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int argc, char* argv[]) {

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_sec;

    int n = std::atoi(argv[1]);
    int m = std::atoi(argv[2]);

    float* image = new float[n*n];
    float* mask = new float[m*m];
    float* output = new float[n*n]();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-10.0f, 10.0f);
    std::uniform_real_distribution<float> dis2(-1.0f, 1.0f);

    for (int i = 0; i < n*n; i++) {
        image[i] = dis(gen);
    }
    for (int j=0; j < m*m; j++) {
        mask[j] = dis2(gen);
    }

    start = high_resolution_clock::now();
    convolve(image, output, n, mask, m);
    end = high_resolution_clock::now();

    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    cout << duration_sec.count() <<"\n";
    cout << output[0] << "\n";
    cout << output[(n*n)-1] << "\n";

    delete[] image;
    delete[] mask;
    delete[] output;

    return 0;

}


    

