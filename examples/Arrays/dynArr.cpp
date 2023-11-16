#include <iostream>
#include <ctime>

int main()
{
    srand(time(nullptr));
    int size;
    std::cout << "Input size: ";
    std::cin >> size;
    int* arr = new int[size];
    //fill array
    for (int i=0; i<size; ++i)
        arr[i] = rand()%size;
    //print array
    for (int i=0; i<size; ++i)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
    //calc average
    double avg = 0.0;
    for (int i=0; i<size; ++i)
        avg += (double)arr[i]/size;
    std::cout << "Average = " << avg << std::endl;
    //clean
    delete[] arr;
    return 0;
}