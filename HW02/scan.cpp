
#include <cstddef>

void scan(const float *arr, float *output, std::size_t n){

    for(int i=0; i < n; i++) {
        float element = 0;
        for (int k=0; k <= i; k++)
        {
            element = element + arr[k];
        }
        output[i] = element;
    }
}

