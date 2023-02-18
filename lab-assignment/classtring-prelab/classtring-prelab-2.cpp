#include <iostream>
#include <string>

using namespace std;

void findAllIndex(string s1, string s2)
{
    int len1 = s1.length();
    int len2 = s2.length();
    int cnt = 0;
    
    for (int i = 0; i < len1 - len2 + 1; ++i)
    {
        if (s1.substr(i, len2) == s2) cout << i << ' ', cnt++;
    }
    
    if (!cnt) cout << -1 << ' ';
}

int main()
{
    string s1 = "Truong Dai Hoc Bach Khoa.";
    string s2 = "a";
    findAllIndex(s1, s2);
}