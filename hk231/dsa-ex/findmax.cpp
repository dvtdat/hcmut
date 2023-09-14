#include <iostream>

template <typename T>
int findMax(T arr[],int n) {
    T mx = arr[0];
    int idx = 0;

    for (int i = 1; i < n; ++i) {
        if (arr[i] >= mx) {
            mx = arr[i];
            idx = i;
        }
    }

    return idx;
}

int main() {

}