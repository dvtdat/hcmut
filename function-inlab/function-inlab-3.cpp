#include <iostream>
#include <cstring>

using namespace std;

void encrypt(char* text, int shift)
{
    shift = shift % 26;
    for (int i = 0; i < strlen(text); ++i)
    {
        int tmp = (int)text[i] + shift;
        if ((int)'a' <= tmp - shift && tmp - shift <= (int)'z' && tmp > (int)'z') tmp = tmp - ('z' - 'a' + 1);
        else if ((int)'A' <= tmp - shift && tmp - shift <= (int)'Z' && tmp > (int)'Z')  tmp = tmp - ('Z' - 'A' + 1);
            
        text[i] = (char)tmp;
    }    
}

void decrypt(char* text, int shift) 
{
    shift = shift % 26;
    for (int i = 0; i < strlen(text); ++i)
    {
        text[i] = text[i] - shift;
        if ('a' <= text[i] + shift && text[i] + shift <= 'z' && text[i] < 'a') text[i] = text[i] + ('z' - 'a' + 1);
        else if ('A' <= text[i] + shift && text[i] + shift <= 'Z' && text[i] < 'A') text[i] = text[i] + ('Z' - 'A' + 1);
    }  
}

int main()
{
    int n, shift; 
    cin >> n >> shift;
    char* text = new char[n + 1];
    for(int i = 0; i < n; i++) cin >> text[i];
    text[n] = 0;

    encrypt(text, shift);
    cout << text << '\n';
    decrypt(text, shift);
    cout << text;

    delete[] text;
}