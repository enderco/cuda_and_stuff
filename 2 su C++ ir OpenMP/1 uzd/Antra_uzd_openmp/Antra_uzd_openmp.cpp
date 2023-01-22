#include <iostream>
#include <omp.h>
#define THREAD_COUNT 10

// Antra versija.
int main()
{
    int data[1000];
    for (int i = 0; i < 1000; i++) {
        data[i] = i;
    }

    float results[THREAD_COUNT];
    int index = 0;
    float arraySum = 0;

    omp_set_num_threads(THREAD_COUNT);
    #pragma omp parallel default(none) shared(data, results, index, std::cout) reduction(+: arraySum)
    {
        const int threadNumber = omp_get_thread_num();
        const int begin = threadNumber * 100;
        const int end = ((threadNumber + 1) * 100) - 1;

        float sum = 0;
        for (int i = begin; i < end + 1; i++) {
            sum = sum + data[i];
        }

        arraySum = sum;
        float average = sum / 100;
        #pragma omp critical
        {
            results[index++] = average;
        }
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        std::cout << "Masyvo indekso " << i << " gautas vidurkio rezultatas: " << results[i] << "\n";
    }

    std::cout << "Visu masyvu suma: " << arraySum << "\n";
}