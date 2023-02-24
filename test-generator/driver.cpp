#include <bits/stdc++.h>

using namespace std;

const string NAME = "main";
const string TESTNAME = "test";

const int minHP = 1, maxHP = 200;
const int minLevel = 1, maxLevel = 2;
const int minItem = 1, maxItem = 99;

//int event[17] = {0, 1, 2, 3, 4, 5, 6, 7, 11, 12, 13, 15, 16, 17, 18, 19, 99};
int event[17] = {0, 1, 2, 3, 4, 5, 6, 7, 5, 4, 5, 3, 4, 4, 5, 5, 1};
//int event[17] = {7, 7, 7, 6, 7, 7, 6, 7, 7, 6, 7, 6, 6, 6, 6, 6, 7};
const int minEvent = 1, maxEvent = 16;

const int minN = 10, maxN = 20;
const int nTest = 200;

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

int main()
{
    srand(time(NULL));
    for (int iTest = 1; iTest <= nTest; ++iTest)
    {
        ofstream inp((TESTNAME +".inp").c_str());

        int healthPoint, level, remedy, maidenKiss, phoenixDown;
        healthPoint = minHP + rand() % (maxHP - minHP + 1);
        level = minLevel + rand() % (maxLevel - minLevel + 1);
        remedy = minItem + rand() & (maxItem - minItem + 1);
        maidenKiss = minItem + rand() & (maxItem - minItem + 1);
        phoenixDown = minItem + rand() & (maxItem - minItem + 1);

        inp << healthPoint << ' ' << level << ' ' << remedy << ' ' << maidenKiss << ' ' << phoenixDown << '\n';

        int n = minN + rand() % (maxN - minN + 1);
        for (int i = 1; i <= n; ++i)
        {
            int index = minEvent + rand() % (maxEvent - minEvent + 1);
            if (event[index] == 13)
            {
                inp << event[index];
                for (int j = 0; j < 4; ++j) inp << 1 + rand() % 4;
                inp << ' ';
            }
            else inp << event[index] << ' ';
        }

        inp << '\n';
        inp << "tc1_mush_ghost,tc1_aclepius_pack,tc1_merlin_pack";
        inp.close();

        system((NAME + ".exe " + TESTNAME + ".inp").c_str());
        system((NAME + "2.exe " + TESTNAME + ".inp").c_str());

        if (system(("fc " + TESTNAME + ".out " + TESTNAME + ".ans").c_str()) != 0)
        {
            cout << "Test " << iTest << " WA\n";
            return 0;
        }

        cout << "Test " << iTest << " AC\n";
        cout << "--------------------------------" << '\n';
    }
}
