#include <cstddef>

void convolve(const float *image, float *output, std::size_t n, const float *mask, std::size_t m)
{
    //the input here is a image 

    int constant_m =(m-1)/2;
    int i,j;

    for (int x = 0; x<n; x++)
    {
        for (int y = 0; y<n; y++)
        {
            float sum = 0.0;

                for (i = 0; i<m; i++)
                {
                    for(j = 0; j<m; j++)
                    {
                        int f_in_val_x = x + i - constant_m;
                        int f_in_val_y = y + j - constant_m;

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
