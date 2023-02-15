#include <iostream>
#include <fstream>

using namespace std;

float a[1000][1000];

void process(string fileName)   
{
    ifstream ip; ip.open(fileName);


    int n, m; ip >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j) ip >> a[i][j];
    }

    float mx, mxOverall = -10000000000;
    for (int i = 0; i < n; ++i)
    {
        mx = -10000000000;
        for (int j = 0; j < m; ++j)
        {
            mx = max(mx, a[i][j]);
            mxOverall = max(mxOverall, a[i][j]);
        }

        cout << mx << ' ';
    }

    cout << mxOverall;
}

int main()
{
    string inputFile = "tmp.txt";
    process(inputFile);
}