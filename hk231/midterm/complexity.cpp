#include <bits/stdc++.h>

using namespace std;

// O(n)
void ExA(int n) {
    int a;
    for (int i = 0; i < n; i += 2) a = i;
}

// O(n ^ 2)
void ExB(int n) {
    int a;
    for (int i = 0; i < n * n; ++i) a = i;
}

// O(n ^ 2)
void ExC(int n) {
    int a;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) a = i;
    }
}

// O(n ^ 4)
void ExD(int n) {
    int a;
    for (int i = 0; i < n * n; ++i) {
        for (int j = 0; j <= i; ++j) a = i;
    }
}

// O(n ^ 2)
void ExE(int n) {
    int a;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n - i; ++j) a = i;
    }
}

// O(log(n))
void ExF(int n) {
    int a;
    for (int i = 1; i < n; i *= 2) a = i;
}


int main() {

}