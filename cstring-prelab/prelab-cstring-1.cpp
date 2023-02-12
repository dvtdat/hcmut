#include <iostream>
#include <cstring>

/* Implement void process(const char *str, char *outstr) function which eliminates redundant space characters 
so that there are no consecutive space characters and there is no space character at the beginning/end of string.*/

void process(char str[], char outstr[]) {
    int n = 0;
    bool flag = false;

    int i = 0;
    while (i <= strlen(str))
    {
        while (str[i] == ' ') i++;
        if (flag && str[i - 1] == ' ') outstr[n++] = ' ';
        else flag = true;
        
        outstr[n++] = str[i++]; 
    }

    outstr[n] = '\0';
}

int main()
{
    char str[] = "hehe";
    char *outstr = new char[strlen(str) + 1];
    process(str, outstr);

    std::cout << outstr << '\n';
}