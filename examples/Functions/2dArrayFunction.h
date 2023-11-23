void printMatrix(int** arr, int rows, int cols);
int** createMatrix(int rows, int cols);
void deleteMatrix(int** matrix, int rows);
void fillArray(int** matrix, int rows, int cols);
int& findMax(int** matrix, int rows, int cols);
void findMax(int** matrix, int rows, int cols, int& result);

namespace tabs {
    void printMatrix(int** arr, int rows, int cols);
}