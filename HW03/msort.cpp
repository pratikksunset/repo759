#include <cstddef>
#include <omp.h>

void merge(int *arr, std::size_t low, std::size_t mid, std::size_t high, int *temp)
{   
    // Merge the two halves into a temporary array
    std::size_t i,j,k;
    i = low;
    j = mid;
    k = low;

    while (i < mid && j < high) //both halves have elements to compare
    {
        if (arr[i] <= arr[j]) 
        {
            temp[k] = arr[i];
            i++;
            k++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
            k++;
        }
    }

    while (i < mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j < high)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }

    std::size_t l;
    for (l = low; l < high; ++l)
    {
        arr[l] = temp[l];
    }
}


static std::size_t min_size(std::size_t a, std::size_t b)
{
    return (a < b) ? a : b;
}
static void serial_mergesort(int *arr, std::size_t left, std::size_t right, int *tmp)
{
    std::size_t n = right - left;
    for (std::size_t width = 1; width < n; width *= 2) {
        for (std::size_t i = left; i < right; i += 2 * width) {
            std::size_t mid = min_size(i + width, right);
            std::size_t last = min_size(i + 2 * width, right);
            if (mid < last)
                merge(arr, i, mid, last, tmp);
        }
    }
}


void msort_compute_func(int *arr, std::size_t low, std::size_t high, int *temp, std::size_t threshold)
{
    //case where the array is less than or equal to the threshold, we do a serial sort.
    if (high - low <= threshold)
    {
        serial_mergesort(arr, low, high, temp);
        return;
    }

    std::size_t mid = (high + low) / 2;

    #pragma omp task shared(arr, temp) firstprivate(mid, low)

    msort_compute_func(arr, low, mid, temp, threshold);

    //here the arr and temop are shared between the two, the write happens between the two.
    //low, mid and high are firstprivate as they are not shared between the two tasks, so copy them
    #pragma omp task shared(arr, temp) firstprivate(mid, high)

    msort_compute_func(arr, mid, high, temp, threshold);

    //let all the tasks finish before merging the two halves. 
    //using taskwait for it.
    #pragma omp taskwait

    merge(arr, low, mid, high, temp);
}

void msort(int* arr, const std::size_t n, const std::size_t threshold)
{
    //first case where there is no need to sort as 0 or 1 element is present.
    if (n <= 1)
    {
        return;
    }

    int *temp = new int[n];

    #pragma omp parallel
    {
        #pragma omp single
        {
            msort_compute_func(arr, 0, n, temp, threshold);
        }
    }
}
