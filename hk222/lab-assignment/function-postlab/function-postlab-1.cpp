#include <iostream>
#include <cstring>

using namespace std;

void mostFrequentCharacter(char* str, char& res, int& freq) 
{ 
    int frequency[50];
    for (int i = 0; i < 50; ++i) frequency[i] = 0;

    for (int i = 0; i < strlen(str); ++i)
    {
        frequency[str[i] - 'a']++;
    }
    
    freq = 0;
    for (int i = 0; i < 50; ++i)
    {
        if (frequency[i] > freq)
        {
            freq = frequency[i];
            res = (char)(i + 'a');
        }
    }
}

int main()
{
    char str[] = "hellohowoldareyouaaaaaaaaaaaaa";
    char res;
    int freq;

    mostFrequentCharacter(str, res, freq);
    cout << res << ' ' << freq << '\n';
}