#include <iostream>

void printMatrix(int** arr, int rows, int cols){
    for (int r=0; r<rows; ++r){
        for (int c = 0; c < cols; ++c)
            std::cout << arr[r][c] << " ";
        std::cout << std::endl;
    }
}

int** createMatrix(int rows, int cols)
{
    int** matrix = new int*[rows];
    for (int r=0; r < rows; ++r)
        matrix[r] = new int[cols];
    return matrix;
}

void deleteMatrix(int** matrix, int rows)
{
    for (int r=0; r < rows; ++r)
        delete[] matrix[r];
    delete[] matrix;
}

void fillArray(int** matrix, int rows, int cols)
{
    for (int r=0; r<rows; ++r)
        for (int c = 0; c < cols; ++c)
            matrix[r][c] = rand()%100;
}

int& findMax(int** matrix, int rows, int cols){
    int max_r = 0;
    int max_c = 0;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c){
            if (matrix[r][c] > matrix[max_r][max_c]){
                max_r = r;
                max_c = c;
            }
        }
    return matrix[max_r][max_c];
}

void findMax(int** matrix, int rows, int cols, int& result){
    result = matrix[0][0];
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (matrix[r][c] > result)
                result = matrix[r][c];
}

