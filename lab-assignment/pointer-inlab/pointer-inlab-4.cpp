#include <iostream>

using namespace std;

char* concatStr(char* str1, char* str2)
{
    int len = 0, i = 0;
    char* tmp = new char[300];
    
    while (str1[i]) tmp[len++] = str1[i++]; i = 0;
    while (str2[i]) tmp[len++] = str2[i++];

    tmp[len] = '\0';

    return tmp;
}

int main()
{
    char s1[] = "Hello, ";
    char s2[] = "Im vai lon";

    char* s = concatStr(s1, s2);
    cout << s;
    delete[] s;
}