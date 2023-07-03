#include <iostream>
#include <cstring>

using namespace std;

bool isPalindrome(const char* str) 
{
    for (int i = 0; i < strlen(str); ++i)
    {
        if (str[i] != str[strlen(str) - i - 1]) return false;
    }

    return true;
}

int main()
{
    const char* str = "axz";
    cout << isPalindrome(str);
}