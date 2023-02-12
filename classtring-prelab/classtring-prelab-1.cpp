#include <iostream>
#include <string>

using namespace std;

/*
Implement the function cutString(string s, int index) to print the 
substring of string s from index position to the end (index from 0).
*/

void cutString(string s, int index)
{
    for (int i = 0; i < s.length(); ++i)
    {
        if (i >= index) cout << s[i];
    }
}

int main()
{
    string s = "Truong Dai Hoc Bach Khoa.";
    cutString(s, 7);
}