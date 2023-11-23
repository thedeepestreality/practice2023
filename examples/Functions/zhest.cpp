#include <iostream>
namespace tabs{
    void printMatrix(int** arr, int rows, int cols){
        for (int r=0; r<rows; ++r){
            for (int c = 0; c < cols; ++c)
                std::cout << arr[r][c] << "\t";
            std::cout << std::endl;
        }
    }
}