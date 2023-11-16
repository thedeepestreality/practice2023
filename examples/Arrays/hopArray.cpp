#include <iostream>

void fillArray(int* arr, int size)
{
    for (int i = 0; i < size; ++i)
        arr[i] = i;
}

void printHopArray(int* arr, int size)
{
    for (int i = 0; i < size/2; ++i)
    {
        std::cout << arr[i] << " " << arr[size - i - 1] << " ";
    }
    if (size % 2 == 1)
        std::cout << arr[size/2] << std::endl;
}

void reverseArray(int* arr, int size)
{
    for (int i=0; i < size/2; ++i)
        std::swap(arr[i], arr[size-i-1]);
}

void shiftArray(int* arr, int size, int shift)
{
    reverseArray(arr, size);
    reverseArray(arr, size - shift);
    reverseArray(arr + size - shift, shift);
}

void printArray(int* arr, int size)
{
    for (int i=0; i< size; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main()
{
    int size;
    std::cout << "Input size: ";
    std::cin >> size;
    int* arr = new int[size];

    fillArray(arr, size);
    printHopArray(arr, size);
    
    std::cout << "Input shift: ";
    int shift;
    std::cin >> shift;
    shift %= size;
    shiftArray(arr, size, shift);
    printArray(arr,size);
    delete[] arr;
    return 0;
}