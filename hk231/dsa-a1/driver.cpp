#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

const int nTest = 10;

const int minMAXSIZE = 5, maxMAXSIZE = 15;
const int minN = 10, maxN = 20;
const int minI = 0, maxI = 15;
const int minV = -10, maxV = 10;
const int minB = 0, maxB = 5;

const string NAME = "main";
const string INP = "INPUT";
const string OUT = "OUTPUT";

const string type[16] = {"RED", "RED", "RED", "RED", "RED", "RED", "RED", "RED", "RED", "RED", "BLUE", "PURPLE", "REVERSAL", "UNLIMITED_VOID", "DOMAIN_EXPANSION", "LIGHT"};
const int light[3] = {-1, 0, 1};

bool driver(int iTest) {
    /* Driver */
    system((NAME + ".exe").c_str());
    system((NAME + "2.exe").c_str());
    
    /* Checker */
    if (system(("fc " + OUT + ".out " + OUT + ".txt").c_str()) != 0) {
        cout << "Test " << iTest << " WA\n"; return false;
    }
    cout << "Test " << iTest << " AC\n" << "--------------------------------" << '\n';
    return true;
}

int main() {
    srand(time(NULL));
    for (int iTest = 1; iTest <= nTest; ++iTest) {
        ofstream inp((INP + ".txt").c_str());
        int MAXSIZE = minMAXSIZE + rand() % (maxMAXSIZE - minMAXSIZE + 1);
        inp << "MAXSIZE " << MAXSIZE << '\n';

        int N = minN + rand() % (maxN - minN + 1);
        int cnt = 0;
        for (int i = 0; i < N; ++i) {
            int idx = minI + rand() % (maxI - minI + 1);

            inp << type[idx];

            if (type[idx] == "RED") {
                inp << " a" << cnt++ << ' ' << minV + rand() % (maxV - minV + 1);
            }

            if (type[idx] == "BLUE") {
                inp << ' ' << rand() % (maxB - minB + 1);
            }

            if (type[idx] == "LIGHT") {
                inp << ' ' << light[rand() % 3];
            }

            inp << (rand() % 3 == 1 ? "\nLIGHT 1\n" : "\n");
        }

        inp << "LIGHT 0\nLIGHT -1\nLIGHT 1";
        inp.close();

        if (!driver(iTest)) return 0;
    }
}