#include <iostream>
#include <fstream>

using namespace std;

void threeChars(string fileName)   
{
    ifstream ip; ip.open(fileName);
    string s;
    while (ip >> s && s != "***")
    {
        if (s[0] <= s[1] && s[1] <= s[2]) cout << "true";
        else cout << "false";
        cout << '\n';
    }
}

int main()
{
    string inputFile = "tmp.txt";
    threeChars(inputFile);
}