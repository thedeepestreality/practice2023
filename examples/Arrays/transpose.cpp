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
            matrix[r][c] = r*cols + c + 1;
}

int main()
{
    int rows;
    int cols;
    std::cout << "Input rows and cols: ";
    std::cin >> rows >> cols;
    int** source = createMatrix(rows, cols);
    printMatrix(source, rows, cols);

    fillArray(source, rows, cols);
    int** transpose = createMatrix(cols, rows);
    for (int r=0; r< rows; ++r)
        for (int c=0; c< cols; ++c)
            transpose[c][r] = source[r][c];
    printMatrix(transpose, cols, rows);
    deleteMatrix(source, rows);
    deleteMatrix(transpose, cols);
    return 0;
}