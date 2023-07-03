#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    char str[] = "vasavasabccbafsafa";
    char res[100] = "";

    char tmp[100] = "";
    char tmprev[100] = "";

    for (int i = 0; i < strlen(str); ++i)
    {
        int j = strlen(str) - 1;
        while (i < j)
        {
            if (str[i] == str[j] && strlen(res) < j - i + 1)
            {
                strncpy(tmp, str + i, j - i + 1); tmp[j - i + 1] = '\0';
                strncpy(tmprev, str + i, j - i + 1); tmprev[j - i + 1] = '\0';

                for (int k = 0; k < strlen(tmp); ++k) tmprev[k] = tmp[strlen(tmp) - k - 1];
                if (strcmp(tmp, tmprev) == 0) strncpy(res, tmp, strlen(tmp));
            }
            j--;
        }
    }

    cout << res << '\n';

    return 0;
}
