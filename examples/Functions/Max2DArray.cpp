#include <iostream>
#include <ctime>
#include "2dArrayFunction.h"

int main()
{
    srand(time(nullptr));
    int rows;
    int cols;
    std::cout << "Input Rows Cols:";
    std::cin >> rows >> cols;
    int** matrix = createMatrix(rows, cols);
    fillArray(matrix, rows, cols);
    printMatrix(matrix, rows, cols);

    int& ref_res = findMax(matrix, rows, cols);
    ref_res = -100;
    int res;
    findMax(matrix, rows, cols, res);
    res = -100;

    deleteMatrix(matrix, rows);

    return 0;
}