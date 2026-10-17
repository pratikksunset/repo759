#include <cstddef>
#include <omp.h>

void convolve(const float *image, float *output, std::size_t n, const float *mask, std::size_t m)
{
    std::size_t constant_m =(m-1)/2;

    #pragma omp parallel for collapse(2)
    for (std::size_t x = 0; x<n; x++)
    {
        for (std::size_t y = 0; y<n; y++)
        {
            float sum = 0.0;

                for (std::size_t i = 0; i<m; i++)
                {
                    for(std::size_t j = 0; j<m; j++)
                    {
                        std::size_t f_in_val_x = x + i - constant_m;
                        std::size_t f_in_val_y = y + j - constant_m;

                        if((f_in_val_x>= 0 && f_in_val_x<n) && (f_in_val_y >=0 && f_in_val_y <n))
                        {
                            sum = sum + (mask[i*m+j]*image[f_in_val_x*n+f_in_val_y]);
                        }
                        else if ((!(f_in_val_x>= 0 && f_in_val_x<n)) && (!(f_in_val_y >=0 && f_in_val_y <n)))
                        {
                            sum = sum + (mask[i*m+j] * 0);
                        }
                        else
                        {
                            sum = sum + (mask[i*m+j]*1); 
                        }
                        
                    }
                }
                output[x*n + y] = sum;
        }
    }

}
