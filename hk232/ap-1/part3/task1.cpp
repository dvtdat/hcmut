#include <bits/stdc++.h>

using namespace std;

int main() {
	int n; cin >> n;

	if (n < 5) {
		cout << "Cost: " << 0 << "$\n";
	} else if (5 <= n && n <= 10) {
		cout << "Cost: " << 10 << "$\n";
	} else if (11 <= n && n <= 16) {
		cout << "Cost: " << 20 << "$\n";
	} else {
		cout << "Cost: " << 25 << "$\n";
	}
}
