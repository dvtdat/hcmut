#include <iostream>
#include <string>

using namespace std;

void deleteWord(string s, string s1)
{
    string outstr = "";
    int prev = 0;
    for (int i = 0; i < s.length(); ++i)
    {
        if (s.substr(i, s1.length()) == s1)
        {
            outstr += s.substr(prev, i - prev);
            prev = i + s1.length();
        }
    }

    outstr += s.substr(prev, s.length() - prev);

    cout << outstr;
}

int main()
{
    string s = "Truong Dai Hoc Bach Khoa, Sai Gon";
    string s1 = "ai ";
    deleteWord(s, s1);
}
