// 

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef long long ll;
typedef long double ld;

const ll infLL = 2e18 + 7;
const int inf = 2e9 + 7;
const int maxN = 200010;
const ll MOD = 998244353;
const double eps = 1e-12;

typedef struct Item* ptr;

struct Item
{
    double coef; // coefficient
    int exp; // exponent
    ptr next;
};

void normalizePolynomial(ptr& first)
{
    ptr cur = first;

    while (cur)
    {
        ptr nxt = cur->next;
        ptr prev = cur;
        while (nxt)
        {
            if (cur->exp == nxt->exp)
            {
                cur->coef += nxt->coef;

                prev->next = nxt->next;
                delete nxt;
                nxt = prev->next;
            }
            else
            {
                prev = nxt;
                nxt = nxt->next;
            }
        }

        cur = cur->next;
    }

    cur = first;
    ptr prev = nullptr;

    while (cur)
    {
        if (cur->coef == 0)
        {
            if (prev)
            {
                prev->next = cur->next;
                delete cur;
                cur = prev->next;
            }
            else
            {
                ptr tmp = cur;
                cur = cur->next;
                delete tmp;
                first = cur; 
            }
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}

void printPolynomial(ptr polynomial)
{
    ptr current = polynomial;
    while (current) {
        std::cout << "(" << current->coef << "," << current->exp << ") ";
        current = current->next;
    }
    std::cout << std::endl;
}

void solve()
{
    ptr polynomial = new Item{1, -1, nullptr};
    polynomial = new Item{-1, -1, polynomial};

    std::cout << "Original Polynomial: ";
    printPolynomial(polynomial);

    normalizePolynomial(polynomial);

    std::cout << "Normalized Polynomial: ";
    printPolynomial(polynomial);

    // Clean up memory
    ptr current = polynomial;
    while (current) {
        ptr temp = current;
        current = current->next;
        delete temp;
    }

}

void setIO(string name)
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL); cout.tie(NULL);
    if (!name.size()) return;

    #ifndef ONLINE_JUDGE
        freopen((name + ".inp").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    #endif
}

int main()
{
    setIO("");
    int test = 1; //cin >> test;
    while (test--) solve();
}

//         _       _      _
//        | |     | |    | |
//      __| |_   _| |_ __| |
//     / _` \ \ / / __/ _` |
//    | (_| |\ V /| || (_| |
//     \__,_| \_/  \__\__,_|
//
//

