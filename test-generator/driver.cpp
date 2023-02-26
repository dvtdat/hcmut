#include <bits/stdc++.h>

using namespace std;

const string NAME = "main";
const string TESTNAME = "test";

const int minHP = 1, maxHP = 200;
const int minLevel = 1, maxLevel = 2;
const int minItem = 1, maxItem = 99;

int event[17] = {0, 1, 2, 3, 4, 5, 6, 7, 11, 13, 15, 16, 17, 11, 7, 6, 1};
//int event[17] = {0, 1, 2, 3, 4, 5, 6, 7, 11, 12, 13, 15, 16, 17, 18, 19, 99};
//int event[17] = {0, 1, 2, 3, 4, 5, 6, 7, 12, 12, 11, 11, 12, 12, 12, 12, 12};

const int minEvent = 1, maxEvent = 16;

const int minN = 45, maxN = 50;
const int minM = 5, maxM = 10;

const int minA = -99, maxA = 100; 
const int minAdd = -10, maxAdd = 10;

const int nTest = 100;

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

        /*TEST FILE*/
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
        inp << "mushGhost.txt,aclepiusPack.txt,merlinPack.txt";
        inp.close();

        /*MUSH GHOST FILE*/

        ofstream inp2("mushGhost.txt");

        int m = minM + rand() % (maxM - minM + 1);
        inp2 << m << '\n';

        int random = rand() % 3;
        if (random == 0)
        {
            int out = minA + rand() % (maxA - minA + 1);
            int add = minAdd + rand() % (maxAdd - minAdd + 1);
            inp2 << out;
            for (int i = 1; i < m; ++i)
            {
                out += add;
                inp2 << ',' << min(maxA, max(minA, out));
            }
        }
        else if (random == 1)
        {
            int out = minA + rand() % (maxA - minA + 1);
            int add = rand() % maxAdd;
            int idx = rand() % m;

            inp2 << max(minA, out - add * (idx + 1));
            for (int i = 1; i < idx - 1; ++i) inp2 << ',' << max(minA, out - add * (idx - i + 1));
            inp2 << ',' << out;
            for (int i = idx; i < m; ++i) inp2 << ',' << max(minA, out - add * (i - idx + 1));
        }
        else
        {
            int tmp = minA + rand() % (maxA - minA + 1);
            inp2 << min(maxA, max(minA, tmp));
            for (int i = 1; i < m; ++i)
            {
                tmp = minA + rand() % (maxA - minA + 1);
                inp2 << ',' << min(maxA, max(minA, tmp));
            }
        }

        inp2.close();

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
