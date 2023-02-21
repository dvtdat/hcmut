#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    ifstream ip;
    ip.open("tc1_mush_ghost");
    
    int n; ip >> n;
    string a[100]; int i = 0;
    string s; getline(ip, s); getline(ip, s);

    stringstream ss(s);
    
    while (ss.good())
    {
        string tmp;
        getline(ss, tmp, ',');
        a[i++] = tmp;
    }

    for (int i = 0; i < n; ++i)
    {
        int tmp;
        stringstream(a[i]) >> tmp;
        cout << tmp + 10 << '\n';
    }

    
    ip.close();
}