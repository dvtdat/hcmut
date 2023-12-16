#include <iostream>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

void interleaveQueue(queue<int>& q) {
    queue<int> q1, q2;

    int n = q.size();

    while (q.size() > n / 2) {
        q1.push(q.front()); q.pop();
    }

    while (q.size()) {
        q2.push(q.front()); q.pop();
    }

    while (q1.size() && q2.size()) {
        q.push(q1.front());
        q.push(q2.front());

        q1.pop(); q2.pop();
    }

    if (q1.size()) q.push(q1.front());
}

int main() {
    queue<int> q;
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int element; cin >> element;
        q.push(element);
    }
    interleaveQueue(q);

    while (!q.empty()){
        cout << q.front() << ' ';
        q.pop();
    }
}