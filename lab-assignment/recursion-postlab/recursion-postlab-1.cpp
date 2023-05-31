#include <iostream>
#include <string>

using namespace std;

bool palindromeRecursion(string s)
{
    if (s.length() <= 1) return true;
    if (s[0] != s[s.length() - 1]) return false;
    if (s.length() >= 2) return palindromeRecursion(s.substr(1, s.length() - 2));
}

int main()
{
    string s;
    while (cin >> s && s != "*")
    {
        cout << (palindromeRecursion(s) ? "True" : "False") << '\n';
    }
}