#include <iostream>
#include <omp.h>
#define THREAD_COUNT 10

// pirma versija
int main15() {
    int data[1000];
    for (int i = 0; i < 1000; i++)
    {
        data[i] = i;
    }

    int data_size = sizeof(data) / sizeof(data[0]);
    std::cout << "Data size: " << data_size << std::endl;
    float average;
    float res[THREAD_COUNT];
    int index = 0;
    int data_section = data_size / THREAD_COUNT;
    #pragma omp parallel num_threads(THREAD_COUNT) default(none) shared(data, data_section, data_size, res, index) private(average)
    {
        // data_section po 100 nariu, tai kiekvienas threadas po 100 tu tasku ir gaus fore.
        average = 0;
        #pragma omp for schedule(static, data_section)
        for (int i = 0; i < data_size; i++) {
            average += data[i];
        }

        average = average / data_section;
        #pragma omp critical
        {
            res[index] = average;
            index++;
        }
    };

    for (int i = 0; i < THREAD_COUNT; i++) {
        std::cout << "Gautas rezultatas: " << res[i] << "\n";
    }
    std::cout << std::endl;
    return 0;
}

// Antra versija.
int main()
{
    int data[1000];
    for (int i = 0; i < 1000; i++) {
        data[i] = i;
    }

    float results[10];
    int freeIndex = 0;
    omp_set_num_threads(10);
    #pragma omp parallel default(none) shared(data, results, freeIndex, std::cout)
    {
        const int threadNumber = omp_get_thread_num();
        const int begin = threadNumber * 100;
        const int end = ((threadNumber + 1) * 100) - 1;

        float sum = 0;
        for (int i = begin; i < end + 1; i++) {
            sum = sum + data[i];
        }

        float average = sum / 100;
        #pragma omp critical
        {
            results[freeIndex] = average;
            std::cout << threadNumber << " - " << " beginAt - " << begin << " endAt - " << end << " sum = " << sum << " average = " << average << " added at index " << freeIndex << "\n";
            freeIndex++;
        }
    }
}
int alah()
{
    int data[100];
    for (int i = 0; i < 100; i++)
    {
        data[i] = i;
    }

    int data_size = sizeof(data) / sizeof(data[0]);
    std::cout << "Data size: " << data_size << std::endl;
    float average;
    float res[THREAD_COUNT];
    int index = 0;
    int data_section = data_size / THREAD_COUNT; 
    #pragma omp parallel num_threads(THREAD_COUNT) default(none) shared(data, data_section, data_size, res, index) private(average)
    {
        average = 0;
        #pragma omp for schedule(static, data_section)
        for (int i = 0; i < data_size; i++) {
            average += data[i];
        }

        average = average / data_section;
        #pragma omp critical
        {
            res[index] = average;
            index++;
        }
    }
    for (int i = 0; i < THREAD_COUNT; i++) {
        std::cout << "Gautas rezultatas: " << res[i] << "\n";
    }
    std::cout << std::endl;
    return 0;
}