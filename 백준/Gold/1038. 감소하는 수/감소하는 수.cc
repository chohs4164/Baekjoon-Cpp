#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    queue<long long> q;
    vector<long long> v;
    v.reserve(1023);

    // 0~9는 모두 감소하는 수 (초기값)
    for (int i = 0; i <= 9; i++) {
        q.push(i);
        v.push_back(i);
    }

    // BFS로 감소하는 수 생성
    while (!q.empty()) {
        long long x = q.front();
        q.pop();

        int last = (int)(x % 10);

        for (int d = 0; d < last; d++) {
            long long next = x * 10 + d;
            q.push(next);
            v.push_back(next);
        }
    }

    sort(v.begin(), v.end());

    if (N >= (int)v.size()) cout << -1;
    else cout << v[N];

    return 0;
}