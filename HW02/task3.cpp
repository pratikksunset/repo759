#include "matmul.h"
#include <random>
#include <chrono>
#include <ratio>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>

using std::cout;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main() {

    high_resolution_clock::time_point start, start2, start3, start4;
    high_resolution_clock::time_point end, end2, end3, end4;
    duration<double, std::milli> duration_sec1,duration_sec2,duration_sec3,duration_sec4;

    int n = 1200;

    double* A = new double[n*n];
    double* B = new double[n*n];

    double* C1 = new double[n*n]();
    double* C2 = new double[n*n]();
    double* C3 = new double[n*n]();
    double* C4 = new double[n*n]();

    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-10.0f, 10.0f);

    for (int i = 0; i < n*n; i++) {
        A[i] = dis(gen);
    }
    for (int j=0; j < n*n; j++) {
        B[j] = dis(gen);
    }

    std::vector<double> vector_A(A, A + (n * n));
    std::vector<double> vector_B(B, B + (n * n));

    start = high_resolution_clock::now();
    mmul1(A, B, C1, n);
    end = high_resolution_clock::now();

    start2 = high_resolution_clock::now();
    mmul2(A, B, C2, n);
    end2 = high_resolution_clock::now();

    start3 = high_resolution_clock::now();
    mmul3(A, B, C3, n);
    end3 = high_resolution_clock::now();

    start4 = high_resolution_clock::now();
    mmul4(vector_A, vector_B, C4, n);
    end4 = high_resolution_clock::now();

    cout << n << "\n";
    duration_sec1 = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
    cout << duration_sec1.count() <<"\n";
    cout << C1[0] <<"\n";
    duration_sec2 = std::chrono::duration_cast<duration<double, std::milli>>(end2 - start2);
    cout << duration_sec2.count() <<"\n";
    cout << C2[0] <<"\n";
    duration_sec3 = std::chrono::duration_cast<duration<double, std::milli>>(end3 - start3);
    cout << duration_sec3.count() <<"\n";
    cout << C3[0] <<"\n";
    duration_sec4 = std::chrono::duration_cast<duration<double, std::milli>>(end4 - start4);
    cout << duration_sec4.count() <<"\n";
    cout << C4[0] <<"\n";



    delete[] A;
    delete[] B;
    delete[] C1;
    delete[] C2;
    delete[] C3;
    delete[] C4;

    return 0;

}


    

