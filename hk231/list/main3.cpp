#include <iostream>

#include "astack.h"
using namespace std;

int Fib(int n) {
    if (n == 0 || n == 1) return 1;
    
    AStack<int> fib;
    fib.push(1);
    fib.push(1);
    
    for (int i = 2; i <= n; ++i) {
        int a = fib.pop();
        int b = fib.pop();
        int c = a + b;

        cout << a << ' ' << b << '\n';        
        fib.push(c);
        fib.push(b);
    }
    
    fib.pop();
    return fib.pop();
}

bool parentheses(const string &L) {
    AStack<char> st;
    
    int i = 0;
    while (i < (int)L.length()) {
        if (L[i] == '(') st.push('(');
        else st.pop();
        i++;
    }
    
    if (st.length()) return 0;
    return 1;
}

int main() {
    cout << parentheses("(((()))))") << '\n';
}