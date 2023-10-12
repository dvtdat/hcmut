#include <iostream>
#include <string>

using namespace std;

string multiply(string s, int n) {
    if (n == 0) return "";
    return s + multiply(s, n - 1);
}

string expand(string s, int& idx) {
    if (idx >= s.size() || s[idx] == ')') return "";

    string res = "";

    if ('a' <= s[idx] && s[idx] <= 'z') {
        res = s[idx];
        idx++;
    } else if ('0' <= s[idx] && s[idx] <= '9') {
        int n = s[idx] - '0';
        idx += 2;
        string tmp = expand(s, idx);
        idx++;
        res = multiply(tmp, n);
    } else if (s[idx] == '(') {
        idx++;
        res = expand(s, idx);
        idx++;
    }

    return res + expand(s, idx);
}

string expand(string s) {
    int idx = 0;
    return expand(s, idx);
}

int main() {
    cout << expand("2(x0(y))3(z)");
    return 0;
}
