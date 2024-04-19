#include <bits/stdc++.h>

using namespace std;

int main() {
	int n = 0;
	for (int i = 0; i < 10; ++i) {
		int u; cin >> u;
		n += u;
	}

	cout << 1.0 * n / 10 << '\n';
}
