#include "matmul.h"
#include <random>
#include <chrono>
#include <ratio>
#include <iostream>
#include <cmath>
#include <cstdio>
//#include <vector>

using std::cout;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int argc, char* argv[]) {

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_sec;

    int n = std::atoi(argv[1]);
    int t = std::atoi(argv[2]);

    float* A = new float[n*n];
    float* B = new float[n*n];
    float* C1 = new float[n*n]();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-10.0f, 10.0f);

    for (int i = 0; i < n*n; i++) {
        A[i] = dis(gen);
    }
    for (int j=0; j < n*n; j++) {
        B[j] = dis(gen);
    }

    omp_set_num_threads(t);

    start = high_resolution_clock::now();
    mmul(A, B, C1, n);
    end = high_resolution_clock::now();


    cout << C1[0] <<"\n";
    cout << C1[n*n-1] <<"\n";
    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
    cout << duration_sec.count() <<"\n";
    

    delete[] A;
    delete[] B;
    delete[] C1;

    return 0;

}
