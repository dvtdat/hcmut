#include <iostream>
#include <fstream>

using namespace std;

void uppercase(string output)   
{
    ofstream op; op.open(output);
    string s; cin >> s;

    for (int i = 0; i < s.length(); ++i)
    {
        if ('a' <= s[i] && s[i] <= 'z') s[i] = s[i] - 'a' + 'A';
    }
    op << s;
}

int main()
{
    string outputFile = "tmp.txt";
    uppercase(outputFile);
}