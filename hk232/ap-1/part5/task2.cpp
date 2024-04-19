#include <iostream>
using namespace std;

const int ROWS = 4;
const int COLS = 4;

int main() {
    int matrix[ROWS][COLS];

    cout << "Enter elements of the 4x4 matrix:" << endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "Matrix:" << endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    int totalSum = 0;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            totalSum += matrix[i][j];
        }
    }
    cout << "\nSum of all elements: " << totalSum << endl;

    cout << "\nSum of elements in each row:" << endl;
    for (int i = 0; i < ROWS; ++i) {
        int rowSum = 0;
        for (int j = 0; j < COLS; ++j) {
            rowSum += matrix[i][j];
        }
        cout << "Row " << i + 1 << ": " << rowSum << endl;
    }

    cout << "\nSum of elements in each column:" << endl;
    for (int j = 0; j < COLS; ++j) {
        int colSum = 0;
        for (int i = 0; i < ROWS; ++i) {
            colSum += matrix[i][j];
        }
        cout << "Column " << j + 1 << ": " << colSum << endl;
    }

    cout << "\nSum of elements in each diagonal:" << endl;
    int mainDiagonalSum = 0;
    int secondaryDiagonalSum = 0;
    for (int i = 0; i < ROWS; ++i) {
        mainDiagonalSum += matrix[i][i];
        secondaryDiagonalSum += matrix[i][COLS - i - 1];
    }
    cout << "Main Diagonal: " << mainDiagonalSum << endl;
    cout << "Secondary Diagonal: " << secondaryDiagonalSum << endl;

    return 0;
}

