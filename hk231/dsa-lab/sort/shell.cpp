#include <iostream>

using namespace std;

template <class T>
class Sorting {
private:
    static void printArray(T* start, T* end) {
        int size = end - start;
        for (int i = 0; i < size; i++)
            cout << start[i] << " ";
        cout << endl;
    }

public:
    static void sortSegment(T* start, T* end, int idx, int gap) {
        int n = end - start - idx;
        T* _start = start + idx;

        for (int i = gap; i < n; i += gap) {
            for (int j = i; (j >= gap) && (_start[j] < _start[j - gap]); j -= gap) {
                swap(_start[j], _start[j - gap]);
            }
        }
    }

    static void ShellSort(T* start, T* end, int* segList, int nSegList) {
        for (int i = nSegList - 1; i >= 0; --i) {
            int gap = segList[i];
            for (int j = 0; j < gap; ++j) {
                sortSegment(start, end, j, gap);
            }
            cout << gap << " segments: ";
            printArray(start, end);
        }
    }
};


int main() {
    int segList[] = {1, 3, 5};
    int nSegList = 3;
    int array[] = { 10, 9, 8 , 7 , 6, 5, 4, 3, 2, 1 };

    Sorting<int>::ShellSort(&array[0], &array[10], &segList[0], nSegList);
}