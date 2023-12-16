#include <bits/stdc++.h>

using namespace std;

int evaluatePostfix(string expr){
    stringstream ss(expr);

    stack<int> st;
    string s;
    while (ss >> s) {
        if (s != "+" && s != "-" && s != "*" && s != "/") {
            int n = stoi(s);
            st.push(n);
            continue;
        }

        int a = st.top(); st.pop();
        int b = st.top(); st.pop();

        if (s == "+") st.push(a + b);
        if (s == "-") st.push(b - a);
        if (s == "*") st.push(a * b);
        if (s == "/") st.push(b / a);
    }

    return st.top();
}

int main() {
    cout << evaluatePostfix("100 200 + 2 / 5 * 7 +") << '\n';
}