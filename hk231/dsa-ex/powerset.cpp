#include <iostream>
#include <vector>

using namespace std;

template <typename T>
vector<vector<T>> powerSet(vector<T> arr) {
    vector<vector<T>> res;
    for (int i = 0; i < (1 << (int)arr.size()); ++i) {
        vector<T> tmp;
        for (int k = 0; k < (int)arr.size(); ++k) {
            if ((1 << k) & i) tmp.push_back(arr[k]);
        }
        res.push_back(tmp);
    }
    return res;
}

int main() {
    vector<int> a;
    a.push_back(1); a.push_back(2); a.push_back(3);

    vector<vector<int>> res = powerSet<int>(a);

    for (int i = 0; i < res.size(); ++i)
    {
        for (int k : res[i]) cout << k << ' '; cout << '\n';
    }
}