#include "knight.h"

void display(int healthPoint, int level, int remedy, int maidenKiss, int phoenixDown, int rescue) 
{
    cout << "HP=" << healthPoint
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenKiss
        << ", phoenixdown=" << phoenixDown
        << ", rescue=" << rescue << endl;
}

void adventureToKoopa(string file_input, int &healthPoint, int &level, int &remedy, int &maidenKiss, int &phoenixDown, int &rescue) 
{
    
    ifstream fileIn;
    fileIn.open(file_input);

    string firstInpStr, secondInpStr, thirdInpStr;
    getline(fileIn, firstInpStr);
    getline(fileIn, secondInpStr);
    getline(fileIn, thirdInpStr);

    cout << firstInpStr << '\n' << secondInpStr << '\n' << thirdInpStr << '\n';

    stringstream ssFirst(firstInpStr);
    stringstream ssSecond(secondInpStr);
    stringstream ssThird(thirdInpStr);
}