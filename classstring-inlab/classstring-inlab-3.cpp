#include <iostream>
#include <string>

int main()
{
    std::string s; std::cin >> s;
    
    int res = 0, cnt = 1;
    for (int i = 1; i < s.length(); ++i)
    {
        if (s[i] != s[i - 1])
        {
            res = std::max(res, cnt); cnt = 1;
            continue;
        }
        cnt++;
    }
    res = std::max(res, cnt);

    std::cout << res;
}