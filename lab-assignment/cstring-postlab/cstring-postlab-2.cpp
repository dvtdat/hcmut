#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    char str[1000];
    cin.getline(str, sizeof(str), '\n');
        
    int res = 1;

    bool visit[26] = { false };

    for (int i = 0; i < strlen(str); ++i)
    {
        memset(visit, false, sizeof(visit));
        for (int j = i; j < strlen(str); ++j)
        {
            if (visit[str[j] - 'a']) break;
            res = max(res, j - i + 1);
            visit[str[j] - 'a'] = true;
        }
    }

    cout << res << '\n';

    return 0;
}
