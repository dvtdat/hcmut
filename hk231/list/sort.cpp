#include <iostream>
#include "llist.h"
#include "alist.h"

using namespace std;

void bubbleSort(int* arr, const int &n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template <typename E>
void bSort(List<E> &L) {
    for (int i = 0; i < L.length(); ++i) {
        L.moveToStart();
        for (int j = 0; j < L.length() - i - 1; ++j) {
            E curr = L.remove();
            E next = L.remove();

            if (curr < next) {
                L.insert(next);
                L.insert(curr);
            }
            else {
                L.insert(curr);
                L.insert(next);
            }
            L.next();
        }
    }
}

template <typename E>
void iSort(List<E> &L) {
    for (int i = 1; i < L.length(); i++) {
        L.moveToPos(i);
        E key = L.getValue();
        
        int j = i - 1;
        while (j >= 0 && L.getValue() > key) {
            L.prev();
            L.remove();
            L.insert(L.getValue());
            j--;
        }
        
        L.remove(); 
        L.insert(key);
    }
}

int main () {
    LList<int> myList;

    myList.append(10);
    myList.append(5);
    myList.append(20);
    myList.append(3);

    for (myList.moveToStart(); myList.currentPos() < myList.length(); myList.next()) {
        cout << myList.getValue() << ' ';
    }
    cout << '\n';

    bSort(myList);

    for (myList.moveToStart(); myList.currentPos() < myList.length(); myList.next()) {
        cout << myList.getValue() << ' ';
    }
    cout << '\n';
}