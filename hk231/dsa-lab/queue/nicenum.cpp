#include <iostream>
#include <vector>
#include <queue>

using namespace std;


long long nthNiceNumber(int n) {
    long long comp = 2;
    long long size = 1;
    while (n > comp) {
        n -= comp;
        comp *= 2;
        size++;
    }
    
    n -= 1;
    queue<long long> q;
    while (size != 0) {
        if (n == 0) {
            q.push(0); size--;
        }
        else {
            q.push(n % 2);
            n /= 2;
            size--;
        }
    }
    
    long long res = 0;
    comp = 1;
    while (!q.empty()) {
        long long it = q.front();
        q.pop();
        if (it==0) res += 2 * comp;
        else res += 5 * comp;
        comp *= 10;
    }
    return res;
}

int main() {
    int n = 10000;
    cout << nthNiceNumber(n) << endl; // Output: 52
    return 0;
}
