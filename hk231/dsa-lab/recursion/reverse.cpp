#include <iostream>
#include <string>

using namespace std;

string get(string s) {
    if ((int)s.length() <= 0 || s[0] == ' ') return "";
    return s[0] + get(s.substr(1, (int)s.length() - 1));
}

string reverseSentence(string s, int& idx) {
    if (idx >= (int)s.length()) return "";
    
    string t = get(s.substr(idx, (int)s.length() - idx));
    idx += t.length() + 1;

    return reverseSentence(s, idx) + t + ' ';
}

string reverseSentence(string s) {
    int idx = 0;
    return reverseSentence(s, idx);
}

int main() {
    int idx = 0;
    cout << reverseSentence("data structure and algorithm is scary", idx);
    return 0;
}
