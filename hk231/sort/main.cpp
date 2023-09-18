#include <iostream>

using namespace std;

int moves = 0, comps = 0;

void printArray(int* arr, const int &n) {
    cout << "arr = [";
    for (int i = 0; i < n - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr[n - 1] << "]\n";
}

void print() {
    cout << "Total moves: " << moves << '\n';
    cout << "Total compares: " << comps << '\n';
    cout << "------------------\n";
    moves = 0, comps = 0;
}

// comps = inversion
// moves = comps + (n - 1) * 2
void insertionSort(int* arr, const int &n) {
    int tmp, j;
    for (int i = 1; i < n; ++i) {
        tmp = arr[i]; moves++;
        for (j = i - 1; j >= 0; --j) {
            comps++;
            if (tmp < arr[j]) {
                arr[j + 1] = arr[j]; moves++;
            } else break;
        }
        arr[j + 1] = tmp; moves++;
        printArray(arr, n);
    }
}

// comps = n * (n - 1) / 2
// moves = (n - 1) * 3
void selectionSort(int* arr, const int &n) {
    int low;
    for (int i = 0; i < n - 1; ++i) {
        low = i;
        for (int j = i + 1; j < n; ++j) {
            comps++;
            if (arr[j] < arr[low]) low = j;
        }
        swap(arr[i], arr[low]); moves += 3;
    }
}

// comps = n * (n - 1) / 2
void bubbleSort(int* arr, const int &n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            comps++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                moves += 3;
            }
        }
    }
}

int main() {
    int n = 7;
    int* arr = new int[7] {5, 16, 20, 12, 1, 40, 22};
    printArray(arr, n);
    insertionSort(arr, n);
    print();

    delete arr;
    return 0;
}