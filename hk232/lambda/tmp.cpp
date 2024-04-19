#include <bits/stdc++.h>

using namespace std;

int total(char* bin) {
    return (*bin == '\0' ? 0 : total(bin + 1) + *bin - '0');
}

int main() {
    char bin[] = "";
    cout << total(bin);
    return 0;
}