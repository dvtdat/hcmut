#include <iostream>
#include <cstring>

/*Implement void process(const char *str, char *outstr) function which reverses the string.*/

void process(char str[], char outstr[])
{
    for (int i = 0; i < strlen(str); ++i)
    {
        outstr[i] = str[strlen(str) - i - 1];
    }

    outstr[strlen(str)] = '\0';
}

int main()
{
    char str[] = "hehe";
    char *outstr = new char[strlen(str) + 1];
    process(str, outstr);

    std::cout << outstr << '\n';
}