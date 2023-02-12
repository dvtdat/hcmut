#include <iostream>
#include <cstring>

/*Implement int calc(const char *str) function which returns the decimal value of binary string str.*/

int calc(char str[])
{
    int res = 0;
    for (int i = 0; i < strlen(str); ++i)
    {
        if (str[strlen(str) - i - 1] == '1') res += (1 << i);
    }
    return res;
}

int main()
{
    char str[] = "0000";

    std::cout << calc(str);
}