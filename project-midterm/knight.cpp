#include "knight.h"

const int inf = 2e9 + 7;
const int maxN = 200010;

int maxHP = 999;
const int maxLevel = 10;
const int maxRemedy = 99;
const int maxMaidenKiss = 99;
const int maxPhoenixDown = 99;

const int minHP = 0;
const int minLevel = 0;
const int minRemedy = 0;
const int minMaidenKiss = 0;
const int minPhoenixDown = 0;

struct Knights
{
    int healthPoint, level, remedy, maidenKiss, phoenixDown;
    int rescue = 0;

    void init(string s)
    {
        stringstream ss(s);
        ss >> healthPoint >> level >> remedy;
        ss >> maidenKiss >> phoenixDown;

        maxHP = healthPoint;
    }

    void healthCheck()
    {
        if (healthPoint < 0)
        {
            if (phoenixDown > 0)
            {            
                healthPoint = maxHP;
                phoenixDown--; return;
            }
            rescue = 0;
        }
    }

} knight;

struct Events
{
    int arr[maxN];
    int num = 0;

    void init(string s)
    {
        stringstream ss(s);
        int intInp;
        while (ss >> intInp) arr[++num] = intInp;
    }

    struct List
    {
        void event0(Knights &knight)
        {
            knight.rescue = 1; return;
        }

        void event1to5(Knights &knight, int type, int index)
        {
            int damage[6] = {0, 10, 15, 45, 75, 85};
            int levelO = index > 6 ? (index % 10 > 5 ? index % 10 : 5) : index % 10;

            if (knight.level > levelO)
            {
                knight.level++; return;
            }
            if (knight.level == levelO) return;

            knight.healthPoint -= levelO * damage[type];
            knight.healthCheck();
        }
    } eventList;

    void lookUp(Knights &knight, int index)
    {
        if (arr[index] == 0) eventList.event0(knight);
        if (1 <= arr[index] && arr[index] <= 5) eventList.event1to5(knight, arr[index], index);
    }


} events;

struct Loots
{
    string lootFile[10];
    int num = 0;

    void init(string s)
    {
        string tmp = "";
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] == ',')
            {
                lootFile[num++] = tmp;
                tmp = "";
            }
            else tmp += s[i];
        }

        lootFile[num] = tmp;
    }
} loot;

void display(Knights knight) 
{
    cout << "HP=" << knight.healthPoint;
    cout << ", level=" << knight.level;
    cout << ", remedy=" << knight.remedy;
    cout << ", maidenkiss=" << knight.maidenKiss;
    cout << ", phoenixdown=" << knight.phoenixDown;
    cout << ", rescue=" << knight.rescue << endl;
}

void dataInput(string file_input, Knights &knight, Events &events)
{
    ifstream fileIn;
    fileIn.open(file_input);

    string firstInpStr, secondInpStr, thirdInpStr;
    getline(fileIn, firstInpStr);
    getline(fileIn, secondInpStr);
    getline(fileIn, thirdInpStr);

    knight.init(firstInpStr);
    events.init(secondInpStr);
    loot.init(thirdInpStr);
}

void adventureToKoopa(string file_input, int &healthPoint, int &level, int &remedy, int &maidenKiss, int &phoenixDown, int &rescue) 
{
    dataInput(file_input, knight, events);

    int i = 0;
    while (i <= events.num && knight.rescue == 0 && knight.healthPoint >= 0)
    {
        //display(knight);
        events.lookUp(knight, ++i);
    }
    if (i == events.num) knight.rescue = 1;

    display(knight);
}