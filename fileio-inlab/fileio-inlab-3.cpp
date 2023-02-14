#include <iostream>
#include <fstream>

using namespace std;

void process(string fileName)   
{
    ifstream ip; ip.open(fileName);

    int n, m;
    ip >> n >> m;

    double mxOverall = -1000.001;

    for (int i = 0; i < n; ++i)
    {
        double mx = -1000.001;

        for (int j = 0; j < m; ++j)
        {
            double v; ip >> v;
            mx = max(v, mx);
        }
        cout << mx << ' ';
        mxOverall = max(mx, mxOverall);
    }
    cout << mxOverall;
}

int main()
{
    string inputFile = "tmp.txt";
    process(inputFile);
}