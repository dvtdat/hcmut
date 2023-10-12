#include <iostream>
#include <string>

using namespace std;

int mininumBracketAdd(const std::string& s, int idx = 0, int balance = 0) {
    if (idx == (int)s.length()) return balance;

    if (s[idx] == '(') return mininumBracketAdd(s, idx + 1, balance + 1);
    if (s[idx] == ')' && balance > 0) return mininumBracketAdd(s, idx + 1, balance - 1);
    return 1 + mininumBracketAdd(s, idx + 1, balance);
}

int main() {
    cout << mininumBracketAdd(")))((");
    return 0;
}
