#include <bits/stdc++.h>

using namespace std;

const string NAME = "main";
const string TEST = "output";
const string ARMY = "army";
const string EVENT = "event";


const int nTest = 20;

/* ArmyKnights File */
const int minKnight = 50,    maxKnight = 50;
const int minHP = 1,        maxHP = 999;
const int minLevel = 1,     maxLevel = 10;
const int minGil = 0,       maxGil = 10;
const int minItem = 0,      maxItem = 5;

/* Events File */
const int minEvent = 250,     maxEvent = 300;
const int cnt = 14;
int event[cnt] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 112, 113, 114};
bool ok[cnt];

void ArmyKnightFile()
{
    ofstream inp((ARMY + ".inp").c_str());

    int nKnights;
    nKnights = minKnight + rand() % (maxKnight - minKnight + 1);

    inp << nKnights << '\n';

    for (int i = 0; i < nKnights; ++i)
    {
        int HP, level, phoenixDownI, gil, antidote;
        HP = minHP + rand() % (maxHP - minHP + 1);
        level = minLevel + rand() % (maxLevel - minLevel + 1);
        phoenixDownI = minItem + rand() % (maxItem - minItem + 1);
        gil = minGil + rand() % (maxGil - minGil + 1);
        antidote = minItem + rand() % (maxItem - minItem + 1);

        inp << HP << ' ' << level << ' ' << phoenixDownI << ' ' << gil << ' ' << antidote << '\n';
    }

    inp.close();
}

void EventFile()
{
    memset(ok, false, sizeof ok);

    ofstream inp((EVENT + ".inp").c_str());

    int nEvent;
    nEvent = minEvent + rand() % (maxEvent - minEvent + 1);

    vector<int> output;
    output.push_back(95);
    output.push_back(96);
    output.push_back(97);
    if (rand() % 2 == 0) output.push_back(98);

    for (int i = 0; i < nEvent; ++i)
    {
        output.push_back(event[rand() % cnt]);
    }

    random_shuffle(output.begin(), output.end());

    output.push_back(99);

    inp << (int)output.size() << '\n';
    for (int i = 0; i < (int)output.size(); ++i)
    {
        inp << output[i] << ' ';
    }

    inp.close();
}

int main()
{
    srand(time(NULL));
    
    for (int iTest = 1; iTest <= nTest; ++iTest)
    {
        ArmyKnightFile();
        EventFile();

        
        /* Driver */
        system((NAME + ".exe").c_str());
        system((NAME + "2.exe").c_str());
        
        /* Checker */
        if (system(("fc " + TEST + ".out " + TEST + ".ans").c_str()) != 0)
        {
            cout << "Test " << iTest << " WA\n"; return 0;
        }
        cout << "Test " << iTest << " AC\n" << "--------------------------------" << '\n';
        
        //cout << "Test " << iTest << " Running...\n" << "--------------------------------" << '\n';
    }
}