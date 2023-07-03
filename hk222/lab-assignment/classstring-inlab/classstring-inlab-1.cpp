#include <iostream>
#include <string>

using namespace std;

void replaceString(string s, string s1, string s2)
{
    for (int i = s.length() - s1.length(); i >= 0; --i)
    {
        bool flag = true;
        for (int j = 0; j < s1.length(); ++j)
        {
            if (s[i + j] != s1[j]) flag = false;
        }
        
        if (flag)
        {
            cout << s.substr(0, i) << s2 << s.substr(i + s1.length()); return;
        }
    }

    cout << s;
}

int main()
{
    string s = "Sai Gon";
    string s1 = "Sai Gon";
    string s2 = " h";
    replaceString(s, s1, s2);
}
