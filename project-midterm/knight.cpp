#include "knight.h"

const int inf = 2e9 + 7;
const int maxN = 200010;

struct Knights
{
    int healthPoint, level, remedy, maidenKiss, phoenixDown, rescue = 0;
} knight;

struct Events
{
    int type[maxN];
    int size;
} event;

void display(Knights knight) 
{
    cout << "HP=" << knight.healthPoint
        << ", level=" << knight.level
        << ", remedy=" << knight.remedy
        << ", maidenkiss=" << knight.maidenKiss
        << ", phoenixdown=" << knight.phoenixDown
        << ", rescue=" << knight.rescue << endl;
}

void dataInput(string file_input, Knights knight, int events[], int &numEvent)
{
    ifstream fileIn;
    fileIn.open(file_input);

    string firstInpStr, secondInpStr, thirdInpStr;
    getline(fileIn, firstInpStr);
    getline(fileIn, secondInpStr);
    getline(fileIn, thirdInpStr);

    stringstream ssFirst(firstInpStr);
    stringstream ssSecond(secondInpStr);
    stringstream ssThird(thirdInpStr);

    ssFirst >> knight.healthPoint >> knight.level >> knight.remedy >> knight.maidenKiss >> knight.phoenixDown >> knight.rescue;
    
    numEvent = 0;
    int intInp;
    string strInp;

    while (ssSecond >> intInp) events[numEvent++] = intInp;
    while (ssThird >> strInp) cout << strInp;

}

void adventureToKoopa(string file_input, int &healthPoint, int &level, int &remedy, int &maidenKiss, int &phoenixDown, int &rescue) 
{
    int events[200000];
    int numEvent;

    dataInput(file_input, knight, events, numEvent);
}