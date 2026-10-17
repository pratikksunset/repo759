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
    int t = std::atoi(argv[2]);

    float* image = new float[n*n];
    float* mask = new float[3*3];
    float* output = new float[n*n]();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-10.0f, 10.0f);
    std::uniform_real_distribution<float> dis2(-1.0f, 1.0f);

    for (int i = 0; i < n*n; i++) {
        image[i] = dis(gen);
    }
    for (int j=0; j < 3*3; j++) {
        mask[j] = dis2(gen);
    }

    omp_set_num_threads(t);

    start = high_resolution_clock::now();
    convolve(image, output, n, mask, 3);
    end = high_resolution_clock::now();

    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    cout << output[0] << "\n";
    cout << output[(n*n)-1] << "\n";
    cout << duration_sec.count() <<"\n";

    delete[] image;
    delete[] mask;
    delete[] output;

    return 0;

}


    

