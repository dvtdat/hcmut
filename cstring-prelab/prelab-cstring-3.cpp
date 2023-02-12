#include <iostream>
#include <cstring>

int calc(char str[])
{
    int res = 0;
    for (int i = 0; i < strlen(str); ++i) 
    {
        res += 1 << (str[strlen(str) - i - 1] == '1' ? i : 0);
    }

    return res;
}

int main()
{
    char str[] = "0000";

    std::cout << calc(str);
}