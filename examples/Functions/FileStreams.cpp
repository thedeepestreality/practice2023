#include <iostream>
#include <fstream>
#include "2dArrayFunction.h"

int** matrixFromFile(const char* path, int& rows, int& cols)
{
    std::ifstream input(path);
    if (!input.is_open()){
        throw "file opening error";
    }
    input >> rows >> cols;
    if (rows > 100)
        throw "too big matrix";
    int** matrix = createMatrix(rows, cols);
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            input >> matrix[r][c];
    return matrix;
}

int main(int argc, const char* argv[]){
    if (argc < 2){
        std::cout << "not enough cmd arguments\n";
        return 2;
    }
    int** matrix;
    int rows;
    int cols;
    try {
        matrix = matrixFromFile(argv[1], rows, cols);
        printMatrix(matrix, rows, cols);
        deleteMatrix(matrix, rows);
    }
    catch(const char* err_msg){
        std::cout << "Error happened: " << err_msg << "\n";
        return 1;
    }

    std::ofstream out("out.txt");
    if (!out.is_open())
    {
        std::cout << "Output file opening error!\n";
        return 2;
    }
    out << 1 << ' ' << 2 << 2.5;
    return 0;
}