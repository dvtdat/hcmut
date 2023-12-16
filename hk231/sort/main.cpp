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
    for (int i = 0; i < n - 1; ++i) {
        for (int j = n - 1; j > i; --j) {
            comps++;
            if (arr[j] < arr[j - 1]) swap(arr[j], arr[j - 1]), moves++;
        }
    }
}

void mergesort(int* arr,int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergesort(arr, left, mid);    
    mergesort(arr, mid + 1, right);

    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];

    for (int i = 0; i < n1; ++i) leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) rightArr[i] = arr[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else arr[k++] = rightArr[j++];
    }

    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

int main() {
    int n = 4;
    int* arr = new int[10] {5, 3, 20, 12};
    printArray(arr, n);
    insertionSort(arr, n);
    printArray(arr, n);
    print();
    
    delete arr;
    return 0;
}