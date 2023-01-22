#include <iostream>
#include <omp.h>
#include <cmath>

#define THREAD_COUNT 10
int main() {
    int sum;
    int arr_sum = 0;
    float res[THREAD_COUNT];
    int index = 0;

    #pragma omp parallel reduction(+ : arr_sum) num_threads(THREAD_COUNT) default(none) shared(res, index, std::cout) private(sum)
    {
        int threadNumber = omp_get_thread_num();
        sum = pow(threadNumber, 2) + pow(threadNumber, 3);
        arr_sum = sum;
        #pragma omp critical
        {
            res[index] = sum;
            index++;
        }
    };


    for (int i = 0; i < THREAD_COUNT; i++) {
        std::cout << "Masyvo narys " << i << " reiksme: " << res[i] << "\n";
    }
    std::cout << std::endl;
    std::cout << "Masyvo suma: " << arr_sum << std::endl;
    return 0;
}